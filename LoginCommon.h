/**
 * @file    LoginCommon.h
 * @brief  登录域公共类型：子编号、枚举、辅助 wire 结构、常量与内联工具
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstddef>
#include <cstdint>

/** @brief 登录域子编号（module=LOGIN） */
enum class LoginMsgSub : uint8_t
{
    C2S_LOGIN_REQ       = 0x01,
    S2C_LOGIN_RSP       = 0x02,
    C2S_REGISTER_REQ    = 0x03,
    S2C_REGISTER_RSP    = 0x04,
    C2S_SELECT_USER_REQ = 0x05,
    S2C_USER_LIST       = 0x06,
    C2S_CREATE_USER_REQ = 0x07,
    S2C_CREATE_USER_RSP = 0x08,
    S2C_ENTER_GAME      = 0x09,
    S2C_GATEWAY_INFO    = 0x0A,
    C2S_GATEWAY_AUTH_REQ = 0x0D,
};

/** @brief 系统域子编号（module=SYSTEM） */
enum class SystemMsgSub : uint8_t
{
    C2S_HEARTBEAT = 0x01,
    S2C_HEARTBEAT = 0x02,
    S2C_KICK      = 0x03,
    S2C_NOTICE    = 0x04,
    S2C_ERROR     = 0x05,
};

/** @brief 网关校验错误码（S2C_ERROR.code） */
enum class GatewayValidateCode : int32_t
{
    OK           = 0,
    UNKNOWN_MSG  = 1,
    BAD_LENGTH   = 2,
    BAD_STATE    = 3,
    BAD_PAYLOAD  = 4,
    RATE_LIMITED = 5,
};

/** @brief 角色名最小长度（创角校验参考） */
constexpr uint32_t MIN_ROLE_NAME_LEN = 2;

/** @brief 角色名最大长度（创角校验参考） */
constexpr uint32_t MAX_ROLE_NAME_LEN = 16;

#pragma pack(push, 1)

/** @brief S2C_USER_LIST 单条角色 wire 格式（变长 body 条目，无 module/sub） */
struct Msg_S2C_UserListEntryWire
{
    uint64_t userID;
    char     name[32];
    uint32_t level;
    uint8_t  vocation;
    uint8_t  sex;
    uint8_t  reserved[2];
};

#pragma pack(pop)

/** @brief 计算 S2C_USER_LIST body 字节数（含 header 前缀 + entries） */
inline size_t userListBodyLen(uint16_t count)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(count) * sizeof(Msg_S2C_UserListEntryWire);
}
