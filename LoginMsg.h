/**
 * @file    LoginMsg.h
 * @brief  登录域 wire 消息体（登录/注册/选角/创角/进世界/心跳/网关错误）
 */

#pragma once
#include "LoginCommon.h"

#pragma pack(push, 1)

/** @brief C→S 登录请求；module=LOGIN(0x00) sub=0x01 */
struct Msg_C2S_LoginReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_LOGIN_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     account[32];
    char     password[32];
    uint32_t zoneId;
    uint8_t  gameType;
    uint8_t  reserved[3];
};

/** @brief C→S 注册请求；module=LOGIN(0x00) sub=0x03 */
struct Msg_C2S_RegisterReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_REGISTER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     account[32];
    char     password[32];
    char     confirmPassword[32];
    uint32_t zoneId;
    uint8_t  gameType;
    uint8_t  reserved[3];
};

/** @brief S→C 注册响应；module=LOGIN(0x00) sub=0x04 */
struct Msg_S2C_RegisterRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_REGISTER_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    char     msg[64];
    uint64_t accid;
};

/** @brief S→C 登录响应；module=LOGIN(0x00) sub=0x02 */
struct Msg_S2C_LoginRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_LOGIN_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    char     msg[64];
    uint64_t userID;
    uint64_t accid;
    char     loginToken[65];
    uint64_t tokenExpireMs;
};

/** @brief C→S Gateway 票据鉴权；module=LOGIN(0x00) sub=0x0D */
struct Msg_C2S_GatewayAuthReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_GATEWAY_AUTH_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     account[32];
    char     loginToken[65];
    uint32_t zoneId;
    uint8_t  gameType;
    uint8_t  reserved[3];
};

/** @brief S→C 角色列表头；module=LOGIN(0x00) sub=0x06 */
struct Msg_S2C_UserListHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_USER_LIST);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    uint16_t count;
};
static_assert(sizeof(Msg_S2C_UserListHeader) == 8,
              "Msg_S2C_UserListHeader must be packed to 8 bytes");

/** @brief C→S 选角进世界；module=LOGIN(0x00) sub=0x05 */
struct Msg_C2S_SelectUserReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_SELECT_USER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;
    uint64_t loginTxnId;
};

/** @brief C→S 创建角色；module=LOGIN(0x00) sub=0x07 */
struct Msg_C2S_CreateUserReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_CREATE_USER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     name[32];
    uint8_t  vocation;
    uint8_t  sex;
    uint8_t  reserved[2];
};

/** @brief S→C 创建角色响应；module=LOGIN(0x00) sub=0x08 */
struct Msg_S2C_CreateUserRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_CREATE_USER_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    char     msg[64];
    uint64_t userID;
};

/** @brief S→C 网关信息；module=LOGIN(0x00) sub=0x0A */
struct Msg_S2C_GatewayInfo
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_GATEWAY_INFO);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    char     gatewayIP[32];
    uint16_t gatewayPort;
    char     msg[64];
};

/** @brief S→C 进入游戏世界；module=LOGIN(0x00) sub=0x09 */
struct Msg_S2C_EnterGame
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_ENTER_GAME);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;
    char     name[32];
    uint32_t mapID;
    float    x, y, z;
    uint32_t level;
    uint32_t hp;
    uint32_t maxHP;
    uint32_t mp;
    uint32_t maxMP;
};

/** @brief C→S 心跳；module=SYSTEM(0x0F) sub=0x01 */
struct Msg_C2S_Heartbeat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::C2S_HEARTBEAT);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t seq;
};

/** @brief S→C 心跳；module=SYSTEM(0x0F) sub=0x02 */
struct Msg_S2C_Heartbeat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_HEARTBEAT);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t seq;
    uint64_t serverTime;
};

/** @brief S→C 网关错误；module=SYSTEM(0x0F) sub=0x05 */
struct Msg_S2C_Error
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_ERROR);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t code;
    char    msg[64];
};

#pragma pack(pop)
