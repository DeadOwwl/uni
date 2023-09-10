from base64 import (
    b64decode,
    b64encode,
)
import typing as tp
from cryptography.hazmat.primitives.asymmetric.x25519 import (
    X25519PrivateKey,
    X25519PublicKey,
)
from cryptography.hazmat.primitives import (
    hashes,
    serialization
)
from cryptography.hazmat.primitives.ciphers import (
    Cipher,
    CipherContext,
    algorithms,
    modes
)
import secrets
from cryptography.hazmat.primitives.kdf.hkdf import HKDF


def get_public_from_private(key: X25519PrivateKey) -> X25519PublicKey:
    return key.public_key()


def generate_elliptic_keys() -> X25519PrivateKey:
    return X25519PrivateKey.generate()


def get_key_hash(key: bytes, length: int = 32, salt: tp.Optional[bytes] = None) -> bytes:
    return HKDF(
                algorithm=hashes.SHA256(),
                length=length,
                salt=salt,
                info=b"handshake data",
            ).derive(key)


def prepare_public_key_to_send(key: X25519PublicKey) -> bytes:
    s = b64encode(
        key.public_bytes(
            encoding=serialization.Encoding.Raw,
            format=serialization.PublicFormat.Raw
        ))
    return s

def create_cipher(aes_hash: bytes, cfb_hash: bytes) -> Cipher:
    return Cipher(algorithms.AES(aes_hash), modes.CFB(cfb_hash))


def decode_key(key: bytes) -> X25519PublicKey:
    return X25519PublicKey.from_public_bytes(b64decode(key))


def update_bytes_by_context(file: bytes, cipher: CipherContext):
    return cipher.update(file)


def encode_key(key: X25519PrivateKey, password: bytes):
    aes_hash = get_key_hash(password, 32)
    cfb_hash = get_key_hash(password, 16)
    cipher = Cipher(algorithms.AES(aes_hash), modes.CFB(cfb_hash))
    encoder = cipher.encryptor()
    return b64encode(encoder.update(
        key.private_bytes(
            encoding=serialization.Encoding.Raw,
            format=serialization.PrivateFormat.Raw,
            encryption_algorithm=serialization.NoEncryption()
        )
    ) + encoder.finalize())


def decode_private_key(key: bytes, password: bytes) -> X25519PrivateKey:
    aes_hash = get_key_hash(password, 32)
    cfb_hash = get_key_hash(password, 16)
    cipher = Cipher(algorithms.AES(aes_hash), modes.CFB(cfb_hash))
    decoder = cipher.decryptor()
    return X25519PrivateKey.from_private_bytes(decoder.update(b64decode(key)) + decoder.finalize())


def decrypt_bytes(session_key: bytes, iv: bytes, content: bytes) -> bytes:
    cipher = Cipher(algorithms.AES(session_key), modes.CFB(b64decode(iv))).decryptor()
    return cipher.update(b64decode(content)) + cipher.finalize()


def encrypt_bytes(session_key: bytes, content: bytes) -> tp.Tuple[bytes, bytes]:
    iv = secrets.token_bytes(16)
    cipher = Cipher(algorithms.AES(session_key), modes.CFB(iv)).encryptor()
    return b64encode(cipher.update(content) + cipher.finalize()), b64encode(iv)
