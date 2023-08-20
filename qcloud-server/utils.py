import configparser
import time
from pathlib import Path
from config import *
import hashlib
import json
import plyvel


def sha256_str(s: str):
    return hashlib.sha256(s.encode('utf-8')).digest()


class RequestData:
    def __init__(self, user_name_sha256: bytes, password_sha256: bytes, req_type: RequestType, data: bytes):
        self.user_name_sha256 = user_name_sha256
        self.password_sha256 = password_sha256
        self.req_type = req_type
        self.data = data

    @staticmethod
    def from_bytes(buf: bytes) -> 'RequestData':
        user_name_sha256 = buf[0:SHA256_DIGEST_LENGTH]
        password_sha256 = buf[SHA256_DIGEST_LENGTH: SHA256_DIGEST_LENGTH * 2]
        req_type = RequestType(buf[SHA256_DIGEST_LENGTH * 2])
        data = buf[SHA256_DIGEST_LENGTH * 2 + 1:]
        return RequestData(user_name_sha256, password_sha256, req_type, data)


class ResponseData:
    def __init__(self, resp_code: ResponseCode, data=bytes()):
        self.resp_code = resp_code
        self.data = data

    def to_bytes(self) -> bytes:
        return bytes([self.resp_code.value]) + self.data


class Packet:
    def __init__(self, size: int, data: bytes):
        self.size = size
        self.data = data

    @staticmethod
    def from_data(data: bytes) -> 'Packet':
        return Packet(len(data), data)

    @staticmethod
    def from_char(ch) -> 'Packet':
        return Packet(1, bytes([ch]))

    def to_bytes(self) -> bytes:
        return struct.pack('<I', self.size) + self.data


class UserUtils:
    @staticmethod
    def create_saves(user_name: str, password: str):
        base_dir = Path(user_data_dir)
        user_folder = base_dir / user_name
        user_folder.mkdir(parents=True, exist_ok=True)
        property_file = user_folder / property_file_name
        config = configparser.ConfigParser()

        cur_stamp = str(int(time.time()))
        config['General'] = {
            'UserName': user_name,
            'Password': password,
            'RegistryTimeStamp': cur_stamp
        }

        with property_file.open('w') as f:
            config.write(f)

    @staticmethod
    def exists_sha256(user_name_sha256: bytes) -> bool:
        path = Path(user_data_dir)
        return user_name_sha256 in [sha256_str(dn.name) for dn in path.iterdir() if dn.is_dir()]

    @staticmethod
    def exists_str(user_name: str) -> bool:
        path = Path(user_data_dir)
        return user_name in [dn.name for dn in path.iterdir() if dn.is_dir()]

    @staticmethod
    def find_user_name_by_sha256(user_name_sha256: bytes) -> str | None:
        path = Path(user_data_dir)
        for d in path.iterdir():
            if d.is_dir():
                if sha256_str(d.name) == user_name_sha256:
                    return d.name
        return None


class UserSaves:
    def __init__(self, user_name_sha256: bytes):
        user_name = UserUtils.find_user_name_by_sha256(user_name_sha256)
        if user_name:
            self.valid = True
            self.property_path = Path(user_data_dir) / user_name / property_file_name
        else:
            self.valid = False
            self.property_path = Path()

    def is_valid(self):
        return self.valid

    def password(self) -> str | None:
        try:
            config = configparser.ConfigParser()
            config.read(self.property_path)
            return config['General']['Password']
        except Exception as e:
            return None

    def password_sha256(self) -> bytes | None:
        pwd = self.password()
        if pwd is None:
            return None
        return sha256_str(pwd)

    def user_name(self) -> str | None:
        try:
            config = configparser.ConfigParser()
            config.read(self.property_path)
            return config['General']['UserName']
        except Exception as e:
            return None

    def registry_timestamp(self) -> int | None:
        try:
            config = configparser.ConfigParser()
            config.read(self.property_path)
            return int(config['General']['RegistryTimeStamp'])
        except Exception as e:
            return None


def save_timers(user_name: str, data: bytes):
    jdata: dict[str, str] = json.loads(data)
    db = plyvel.DB(str(Path(user_data_dir) / user_name / 'Timer-DB'), create_if_missing=True)
    for timer, record in jdata.items():
        db.put(timer.encode('utf-8'), record.encode('utf-8'))
    db.close()


def load_timers(user_name: str) -> dict[str, str] | None:
    db_path = Path(user_data_dir) / user_name / 'Timer-DB'

    # Check if the directory exists
    if not db_path.exists():
        return None

    db = plyvel.DB(str(db_path), create_if_missing=True)

    data_dict = {}
    for key, value in db.iterator():
        data_dict[key.decode('utf-8')] = value.decode('utf-8')

    db.close()

    return data_dict
