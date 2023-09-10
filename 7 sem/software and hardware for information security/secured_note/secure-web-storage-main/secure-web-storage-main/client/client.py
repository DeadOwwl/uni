from client_crypto_utils import *
import requests
from io import BytesIO


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
        pass_enc, pass_iv = encrypt_bytes(self.derived_session_key, get_key_hash(self.password.encode()))
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

    def save_key(self) -> None:
        with open("pass.txt", 'wb') as writer:
            writer.write(encode_key(self._private_key, self.password.encode()))


if __name__ == "__main__":
    print("You need to authorize")
    login = input("Please, input your login: ")
    password = input("Please, input your password: ")
    restore_yn = input("Restore last key? Y/N: ")
    signup = input("You already signup? Y/N: ")
    client = Client(login, password, restore_yn.lower() == "y")
    client.auth()
    if signup.lower() == "y":
        while not client.try_login():
            print("Your creds are incorrect, double check them")
            login = input("Please, input your login: ")
            password = input("Please, input your password: ")
            client.login = login
            client.password = password
    else:
        while not client.try_signup():
            print("Your login already occupied, send another creds")
            login = input("Please, input your login: ")
            password = input("Please, input your password: ")
            client.login = login
            client.password = password
        client.try_login()

    while True:
        action = input("What do you want to do?\n1. Get file;\n2. Create file;\n3. Update file;\n4. Delete file;"
                       "\n5. Save key and quit\n")
        try:
            action_num = int(action)
        except ValueError:
            print("Please, input number from 1 to 5")
            continue

        if 1 <= action_num <= 4:
            filename = input("Please input a filename to your file: ")

        if action_num == 1:
            file_content = client.get_file(filename)
            with open(filename, 'w') as writer:
                writer.write(file_content.decode())
        elif action_num == 2:
            with open(filename) as reader:
                client.update_file(filename, "\n".join(reader.readlines()).encode())
        elif action_num == 3:
            with open(filename) as reader:
                client.update_file(filename, "\n".join(reader.readlines()).encode())
        elif action_num == 4:
            client.delete_file(filename)
        elif action_num == 5:
            client.save_key()
            print("Bye")
            break
        else:
            print("I don't understand, please try again")
