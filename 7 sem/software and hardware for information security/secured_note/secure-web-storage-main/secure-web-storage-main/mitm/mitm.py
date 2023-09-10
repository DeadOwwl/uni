import requests
from fastapi import (
    Depends,
    FastAPI,
    Response,
)
from pydantic import BaseModel

from client_crypto_utils import *


class Client:
    def __init__(
            self,
            login: str,
            password: str,
            restore_private_key: bool = False,
            server_ip: str = "127.0.0.1",
            server_port: int = 8000
    ) -> None:
        self.login = login
        self.password = password
        if not restore_private_key:
            self._private_key = generate_elliptic_keys()
        else:
            with open("pass.txt", 'rb') as reader:
                key_bytes = reader.readline()
            self._private_key = decode_private_key(key_bytes, password.encode())
        self._public_key = self._private_key.public_key()
        self.server_url = f"http://{server_ip}:{server_port}"
        self._session_key = None
        self._token = None
        self.derived_session_key = None

    def auth(self):
        response = requests.post(self.server_url + "/auth/create_session", json={
            "public_key": prepare_public_key_to_send(self._public_key)
        })
        if response.ok:
            server_pub_key = decode_key(response.json()["public_key"])
            self._token = response.cookies.get("session")
            self._session_key = self._private_key.exchange(server_pub_key)
            self.derived_session_key = get_key_hash(self._session_key)

    def _prepare_creds(self) -> tp.Tuple[bytes, bytes, bytes, bytes]:
        login_enc, login_iv = encrypt_bytes(self.derived_session_key, self.login.encode())
        pass_enc, pass_iv = encrypt_bytes(self.derived_session_key, self.password)
        return login_enc, login_iv, pass_enc, pass_iv

    def try_signup(self) -> bool:
        login_enc, login_iv, pass_enc, pass_iv = self._prepare_creds()
        response = requests.post(self.server_url + "/auth/signup", json={
            "login": login_enc,
            "login_iv": login_iv,
            "pass_hash": pass_enc,
            "pass_iv": pass_iv
        }, cookies={"session": self._token})
        return not (response.status_code == 403 and response.json()["detail"] == "Account already exists")

    def try_login(self) -> bool:
        login_enc, login_iv, pass_enc, pass_iv = self._prepare_creds()
        response = requests.post(self.server_url + "/auth/login", json={
            "login": login_enc,
            "login_iv": login_iv,
            "pass_hash": pass_enc,
            "pass_iv": pass_iv
        }, cookies={"session": self._token})

        if response.status_code == 401 and response.json()["detail"] == "Login does not exist":
            return self.try_signup()
        else:
            return not response.status_code == 401

    @staticmethod
    def _check_token_outdated(response: requests.Response) -> bool:
        return response is not None and response.status_code == 401 and response.json()["detail"] == "token outdated"

    def _auth_and_login(self) -> None:
        self.auth()
        self.try_login()

    def get_file(self, filename: str) -> bytes:
        response = requests.get(self.server_url + "/files/" + filename, cookies={"session": self._token})
        if self._check_token_outdated(response):
            self._auth_and_login()
            return self.get_file(filename)
        if response.ok:
            response_json = response.json()
            return decrypt_bytes(self.derived_session_key, response_json["iv"], response_json["content"])

    def update_file(self, filename: str, file: bytes) -> None:
        encrypted, iv = encrypt_bytes(self.derived_session_key, file)
        response = requests.put(self.server_url + "/files/" + filename,
                                json={"content": encrypted, "iv": iv},
                                cookies={"session": self._token})
        if self._check_token_outdated(response):
            self._auth_and_login()
            self.update_file(filename, file)

    def delete_file(self, filename: str) -> None:
        response = requests.delete(self.server_url + "/files/" + filename, cookies={"session": self._token})
        if self._check_token_outdated(response):
            self._auth_and_login()
            self.delete_file(filename)

app = FastAPI()


def hash_bytes(content: bytes) -> bytes:
    h = hashes.Hash(hashes.SHA256())
    h.update(content)
    return h.finalize()


class Credentials(BaseModel):
    login: str
    pass_hash: bytes


class Account(BaseModel):
    stored_hash: bytes
    salt: bytes

    @staticmethod
    def create(creds: Credentials) -> 'Account':
        salt = secrets.token_bytes(8)
        stored_hash = hash_bytes(creds.pass_hash + salt)
        return Account(stored_hash=stored_hash, salt=salt)


class Session(BaseModel):
    key: bytes


def encrypt_bytes2(key: bytes, content: bytes) -> tp.Tuple[bytes, bytes]:
    iv = secrets.token_bytes(16)
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))
    encryptor = cipher.encryptor()
    return encryptor.update(content) + encryptor.finalize(), iv


def decrypt_bytes2(key: bytes, iv: bytes, content: bytes) -> bytes:
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))
    decryptor = cipher.decryptor()
    return decryptor.update(content) + decryptor.finalize()


class EncryptedData(BaseModel):
    content: bytes
    iv: bytes

    def decrypt(self, session: Session) -> bytes:
        content = b64decode(self.content)
        iv = b64decode(self.iv)
        return decrypt_bytes2(session.key, iv, content)

    @staticmethod
    def encrypt(session: Session, content: bytes) -> 'EncryptedData':
        encrypted, iv = encrypt_bytes2(session.key, content)
        return EncryptedData(content=b64encode(encrypted), iv=b64encode(iv))


class PublicKey(BaseModel):
    public_key: bytes


client_session = Session(key=b"")
client = Client("", "")


@app.post("/auth/create_session")
def create_session(client_pkey_body: PublicKey, response: Response):
    """
    Receive an EC public key and create the session token and own EC keys.
    """
    global client_session, client
    client_pkey_bytes = b64decode(client_pkey_body.public_key)
    client_pkey = X25519PublicKey.from_public_bytes(client_pkey_bytes)
    private_key = X25519PrivateKey.generate()
    shared_key = private_key.exchange(client_pkey)
    derived_key = HKDF(
        algorithm=hashes.SHA256(),
        length=32,
        salt=None,
        info=b"handshake data",
    ).derive(shared_key)
    client_session.key = derived_key

    client.auth()

    response.set_cookie(key="session", value=client._token)
    server_pkey_bytes = private_key.public_key().public_bytes(
        encoding=serialization.Encoding.Raw,
        format=serialization.PublicFormat.Raw,
    )
    return {"public_key": b64encode(server_pkey_bytes)}


class EncryptedCreds(BaseModel):
    login: bytes
    login_iv: bytes
    pass_hash: bytes
    pass_iv: bytes


def decrypt_creds(enc_creds: EncryptedCreds):
    login = decrypt_bytes2(
        client_session.key,
        b64decode(enc_creds.login_iv),
        b64decode(enc_creds.login),
    )
    pass_hash = decrypt_bytes2(
        client_session.key,
        b64decode(enc_creds.pass_iv),
        b64decode(enc_creds.pass_hash),
    )
    return Credentials(login=login, pass_hash=pass_hash)


@app.post("/auth/signup", status_code=201)
def signup(creds: Credentials = Depends(decrypt_creds)):
    print(creds)
    client.login = creds.login
    client.password = creds.pass_hash
    client.try_signup()


@app.post("/auth/login", status_code=204)
def login(creds: Credentials = Depends(decrypt_creds)):
    print(creds)
    client.login = creds.login
    client.password = creds.pass_hash
    client.try_login()


@app.get("/files/{filename}")
def get_file(filename: str):
    raw_data = client.get_file(filename)
    print(raw_data)
    encrypted = EncryptedData.encrypt(client_session, raw_data)
    return encrypted.dict()


@app.put("/files/{filename}")
def save_file(filename: str, encrypted: EncryptedData):
    raw_data = encrypted.decrypt(client_session)
    print(raw_data)
    client.update_file(filename, raw_data)


@app.delete("/files/{filename}", status_code=204)
def delete_file(filename: str):
    client.delete_file(filename)
