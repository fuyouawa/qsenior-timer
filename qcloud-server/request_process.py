from utils import *


def request_process(request: RequestData):
    if request.req_type != RequestType.LOG_IN:
        user = UserSaves(request.user_name_sha256)
        if not user.is_valid():
            return ResponseData(ResponseCode.USER_NAME_ERR)
        elif user.password_sha256() != request.password_sha256:
            return ResponseData(ResponseCode.PASSWORD_ERR)

    if request.req_type == RequestType.SIGN_IN:
        return request_signin(request)
    elif request.req_type == RequestType.LOG_IN:
        return request_login(request)
    elif request.req_type == RequestType.GET_USER_PROPERTY:
        return request_get_user_property(request)
    elif request.req_type == RequestType.UPLOAD_TIMERS:
        return request_upload_timers(request)
    elif request.req_type == RequestType.DOWNLOAD_TIMERS:
        return request_download_timers(request)

    raise ValueError("未知请求类型!")


def request_signin(request: RequestData):
    return ResponseData(ResponseCode.SUCCESS)


def request_login(request: RequestData):
    user_name, password = [item.decode('utf-8') for item in request.data.split(b'\x00')[:2]]
    if UserUtils.exists_str(user_name):
        return ResponseData(ResponseCode.USER_NAME_REPEAT)
    else:
        UserUtils.create_saves(user_name, password)
        return ResponseData(ResponseCode.SUCCESS)


def request_get_user_property(request: RequestData):
    return ResponseData(
        ResponseCode.SUCCESS,
        struct.pack('<Q', UserSaves(request.user_name_sha256).registry_timestamp())
    )


def request_upload_timers(request: RequestData):
    save_timers(UserSaves(request.user_name_sha256).user_name(), request.data)
    return ResponseData(ResponseCode.SUCCESS)


def request_download_timers(request: RequestData):
    res = load_timers(UserSaves(request.user_name_sha256).user_name())
    if not res:
        return ResponseData(ResponseCode.NO_SAVES)
    return ResponseData(ResponseCode.SUCCESS, json.dumps(res).encode('utf-8'))
