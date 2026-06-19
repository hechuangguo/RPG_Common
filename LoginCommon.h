/**
 * @file    LoginCommon.h
 * @brief  登录域公共类型：子编号、枚举、辅助 wire 结构、常量与内联工具
 *
 * 对应 ClientModule::LOGIN(0x00) 与 ClientModule::SYSTEM(0x0F) 中登录相关子编号。
 * wire 结构体见 LoginMsg.h。
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstddef>
#include <cstdint>

/** @brief 登录域子编号（module=LOGIN） */
enum class LoginMsgSub : uint8_t
{
    C2S_LOGIN_REQ        = 0x01, /**< C→S: 账号密码登录；处理方 LoginServer */
    S2C_LOGIN_RSP        = 0x02, /**< S→C: 登录结果；处理方 LoginServer */
    C2S_REGISTER_REQ     = 0x03, /**< C→S: 注册账号；处理方 LoginServer */
    S2C_REGISTER_RSP     = 0x04, /**< S→C: 注册结果；处理方 LoginServer */
    C2S_SELECT_USER_REQ  = 0x05, /**< C→S: 选角进世界；处理方 Gateway→Super */
    S2C_USER_LIST        = 0x06, /**< S→C: 角色列表（变长）；处理方 GatewayServer（鉴权后推送） */
    C2S_CREATE_USER_REQ  = 0x07, /**< C→S: 创建角色；处理方 Gateway→Record */
    S2C_CREATE_USER_RSP  = 0x08, /**< S→C: 创角结果；处理方 GatewayServer */
    S2C_ENTER_GAME       = 0x09, /**< S→C: 进入游戏世界；处理方 Gateway */
    S2C_GATEWAY_INFO     = 0x0A, /**< S→C: 下发网关地址；处理方 LoginServer */
    C2S_GATEWAY_AUTH_REQ = 0x0D, /**< C→S: Gateway 首包票据鉴权；处理方 Gateway */
    C2S_LOGOUT_REQ       = 0x0E, /**< C→S: 离世界/退出；处理方 GatewayServer */
    S2C_LOGOUT_RSP       = 0x0F, /**< S→C: 离世界响应；处理方 GatewayServer */
};

/**
 * @brief C2S_LOGOUT_REQ.action：客户端退出意图
 */
enum class LogoutAction : uint8_t
{
    RETURN_CHAR_SELECT = 1, /**< 回选角，保持 Gateway 账号会话 */
    RETURN_LOGIN       = 2, /**< 回登录 UI，客户端随后断 Gateway */
};

/** @brief 系统域子编号（module=SYSTEM） */
enum class SystemMsgSub : uint8_t
{
    C2S_HEARTBEAT = 0x01, /**< C→S: 客户端心跳；处理方 Gateway/Login */
    S2C_HEARTBEAT = 0x02, /**< S→C: 心跳响应（含 serverTime）；处理方 Gateway/Login */
    S2C_KICK      = 0x03, /**< S→C: 踢线通知；处理方 Gateway */
    S2C_NOTICE    = 0x04, /**< S→C: 系统公告；处理方 Gateway/Scene */
    S2C_ERROR     = 0x05, /**< S→C: 网关校验失败；处理方 Gateway */
};

/** @brief 网关校验错误码（Msg_S2C_Error.code） */
enum class GatewayValidateCode : int32_t
{
    OK           = 0, /**< 通过（正常流程不发送本消息） */
    UNKNOWN_MSG  = 1, /**< 未登记 module/sub */
    BAD_LENGTH   = 2, /**< 包长与 Validator 规则不匹配 */
    BAD_STATE    = 3, /**< 连接状态不允许（如未鉴权即发场景包） */
    BAD_PAYLOAD  = 4, /**< 字段非法（如空账号、非法 zoneId） */
    RATE_LIMITED = 5, /**< 频率限制 */
};

/** @brief 角色名最少码点数（创角校验，规则见 sdk/util/RoleNameUtil.h） */
constexpr uint32_t MIN_ROLE_NAME_CHAR_COUNT = 2;

/** @brief 角色名最多码点数 */
constexpr uint32_t MAX_ROLE_NAME_CHAR_COUNT = 12;

/** @brief wire/DB 角色名最大 UTF-8 字节数（char[32] 留 \\0） */
constexpr uint32_t MAX_ROLE_NAME_BYTES = 31;

/** @deprecated 同 MIN_ROLE_NAME_CHAR_COUNT */
constexpr uint32_t MIN_ROLE_NAME_LEN = MIN_ROLE_NAME_CHAR_COUNT;

/** @deprecated 同 MAX_ROLE_NAME_CHAR_COUNT */
constexpr uint32_t MAX_ROLE_NAME_LEN = MAX_ROLE_NAME_CHAR_COUNT;

#pragma pack(push, 1)

/**
 * @brief S2C_USER_LIST 单条角色 wire 格式
 *
 * 变长 body 尾随条目，不含 module/sub 前缀。
 */
struct Msg_S2C_UserListEntryWire
{
    uint64_t userID;      /**< 角色 ID */
    char     name[32];    /**< 角色名 UTF-8（2–12 码点，中英文/数字/_） */
    uint32_t level;       /**< 等级 */
    uint8_t  vocation;    /**< 职业 */
    uint8_t  sex;         /**< 性别 */
    uint8_t  reserved[2]; /**< 对齐保留 */
};

#pragma pack(pop)

/**
 * @brief 计算 S2C_USER_LIST body 字节数
 * @param count 角色条目数
 * @return sizeof(header 前缀 + code + count) + count × sizeof(EntryWire)
 */
inline size_t userListBodyLen(uint16_t count)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(count) * sizeof(Msg_S2C_UserListEntryWire);
}
