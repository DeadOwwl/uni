import datetime
import pickle
import secrets
import typing as tp
from base64 import (b64decode, b64encode)
from pathlib import Path

from cryptography.hazmat.primitives import (hashes, serialization)
from cryptography.hazmat.primitives.asymmetric.x25519 import (X25519PrivateKey, X25519PublicKey)
from cryptography.hazmat.primitives.ciphers import (algorithms, Cipher, modes)
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from fastapi import (
    Cookie,
    Depends,
    FastAPI,
    HTTPException,
    Response,
)
from pydantic import BaseModel

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


accounts = {}


def load_state() -> None:
    global accounts
    filepath = Path("accounts.pickle")
    if filepath.is_file():
        accounts = pickle.load(filepath.open("rb"))


def store_state() -> None:
    filepath = Path("accounts.pickle")
    pickle.dump(accounts, filepath.open("wb"))


class Session(BaseModel):
    key: bytes
    login: tp.Optional[str] = None
    pass_hash: tp.Optional[bytes] = None
    expiration_time: datetime.datetime


def encrypt_bytes(key: bytes, content: bytes) -> tp.Tuple[bytes, bytes]:
    iv = secrets.token_bytes(16)
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))
    encryptor = cipher.encryptor()
    return encryptor.update(content) + encryptor.finalize(), iv


def decrypt_bytes(key: bytes, iv: bytes, content: bytes) -> bytes:
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))
    decryptor = cipher.decryptor()
    return decryptor.update(content) + decryptor.finalize()


class EncryptedData(BaseModel):
    content: bytes
    iv: bytes

    def decrypt(self, session: Session) -> bytes:
        content = b64decode(self.content)
        iv = b64decode(self.iv)
        return decrypt_bytes(session.key, iv, content)

    @staticmethod
    def encrypt(session: Session, content: bytes) -> 'EncryptedData':
        encrypted, iv = encrypt_bytes(session.key, content)
        return EncryptedData(content=b64encode(encrypted), iv=b64encode(iv))


sessions = {}


class PublicKey(BaseModel):
    public_key: bytes


@app.post("/auth/create_session")
def create_session(client_pkey_body: PublicKey, response: Response):
    """
    Receive an EC public key and create the session token and own EC keys.
    """
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

    while True:
        token = secrets.token_urlsafe(16)
        if token not in sessions:
            break
    sessions[token] = Session(
        key=derived_key,
        expiration_time=datetime.datetime.now(datetime.timezone.utc) \
            + datetime.timedelta(minutes=1),
    )
    response.set_cookie(key="session", value=token)
    server_pkey_bytes = private_key.public_key().public_bytes(
        encoding=serialization.Encoding.Raw,
        format=serialization.PublicFormat.Raw,
    )
    return {"public_key": b64encode(server_pkey_bytes)}


def get_session(session: tp.Optional[str] = Cookie(None)) -> Cipher:
    if session is None:
        raise HTTPException(401, detail="Missing session")
    if session not in sessions:
        raise HTTPException(401, detail="Incorrect session")
    sess = sessions[session]
    if datetime.datetime.now(datetime.timezone.utc) > sess.expiration_time:
        raise HTTPException(401, detail="token outdated")
    return sess


class EncryptedCreds(BaseModel):
    login: bytes
    login_iv: bytes
    pass_hash: bytes
    pass_iv: bytes


def decrypt_creds(
        enc_creds: EncryptedCreds,
        session: Session = Depends(get_session)):
    login = decrypt_bytes(
        session.key,
        b64decode(enc_creds.login_iv),
        b64decode(enc_creds.login),
    )
    pass_hash = decrypt_bytes(
        session.key,
        b64decode(enc_creds.pass_iv),
        b64decode(enc_creds.pass_hash),
    )
    return Credentials(login=login, pass_hash=pass_hash)


@app.post("/auth/signup", status_code=201)
def signup(creds: Credentials = Depends(decrypt_creds)):
    load_state()
    if creds.login in accounts:
        raise HTTPException(status_code=403, detail="Account already exists")
    accounts[creds.login] = Account.create(creds)
    store_state()


@app.post("/auth/login", status_code=204)
def login(
        creds: Credentials = Depends(decrypt_creds),
        session: Session = Depends(get_session)):
    load_state()
    if creds.login not in accounts:
        raise HTTPException(status_code=401, detail="Login does not exist")
    acc = accounts[creds.login]
    if hash_bytes(creds.pass_hash + acc.salt) != acc.stored_hash:
        raise HTTPException(status_code=401, detail="Wrong password")
    session.login = creds.login
    session.pass_hash = creds.pass_hash


@app.get("/files/{filename}")
def get_file(
        filename: str,
        session: Session = Depends(get_session)):
    if session.login is None or session.pass_hash is None:
        raise HTTPException(status_code=401)
    filedir = Path("data") / session.login
    filedir.mkdir(parents=True, exist_ok=True)
    filepath = filedir / filename
    if not filepath.is_file():
        raise HTTPException(status_code=404)
    stored_data = filepath.read_bytes()
    iv, stored_data = stored_data[:16], stored_data[16:]
    raw_data = decrypt_bytes(session.pass_hash, iv, stored_data)
    encrypted = EncryptedData.encrypt(session, raw_data)
    return encrypted.dict()


@app.put("/files/{filename}")
def save_file(
        filename: str,
        encrypted: EncryptedData,
        session: Session = Depends(get_session)):
    if session.login is None or session.pass_hash is None:
        raise HTTPException(status_code=401)
    filedir = Path("data") / session.login
    filedir.mkdir(parents=True, exist_ok=True)
    filepath = filedir / filename
    raw_data = encrypted.decrypt(session)
    stored_data, iv = encrypt_bytes(session.pass_hash, raw_data)
    filepath.write_bytes(iv + stored_data)


@app.delete("/files/{filename}", status_code=204)
def delete_file(filename: str, session: Session = Depends(get_session)):
    if session.login is None or session.pass_hash is None:
        raise HTTPException(status_code=401)
    filepath = Path("data") / session.login / filename
    filepath.unlink(missing_ok=True)
