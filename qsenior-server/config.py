import asyncio
import struct
from enum import Enum

user_data_dir = r'E:\Resources\Test'
property_file_name = 'property.ini'


class RequestType(Enum):
    SIGN_IN = 0
    LOG_IN = 1
    GET_USER_PROPERTY = 2


class ResponseCode(Enum):
    SUCCESS = 0
    USER_NAME_ERR = 1
    PASSWORD_ERR = 2
    USER_NAME_REPEAT = 3


SHA256_DIGEST_LENGTH = 32
