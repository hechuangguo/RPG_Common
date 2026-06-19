/**
 * @file    LoginMsg.h
 * @brief  登录域 wire 消息体（登录/注册/选角/创角/进世界/心跳/网关错误）
 *
 * 子编号见 LoginCommon.h；字段语义以本文件为权威定义。
 */

#pragma once
#include "LoginCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 登录请求
 *
 * 方向：Client → LoginServer（ClientListen 9010）
 * 编号：module=LOGIN(0x00) sub=0x01
 * 触发：连接 LoginServer 后发送账号密码与所选区服
 */
struct Msg_C2S_LoginReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_LOGIN_REQ);

    ClientMsgByte module = kModule;  /**< 指令编号，须与 MsgHeader.module 一致 */
    ClientMsgByte sub    = kSub;     /**< 子编号，须与 MsgHeader.sub 一致 */
    char     account[32];            /**< 账号 */
    char     password[32];           /**< 密码（明文，仅内网测试环境） */
    uint32_t zoneId;                 /**< 所选游戏区 ID */
    uint8_t  gameType;               /**< 游戏类型（多游戏共用登录服时区分） */
    uint8_t  reserved[3];            /**< 对齐保留 */
};

/**
 * @brief C→S: 注册请求
 *
 * 方向：Client → LoginServer
 * 编号：module=LOGIN(0x00) sub=0x03
 * 触发：注册新账号
 */
struct Msg_C2S_RegisterReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_REGISTER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     account[32];            /**< 账号 */
    char     password[32];           /**< 密码 */
    char     confirmPassword[32];    /**< 确认密码（须与 password 一致） */
    uint32_t zoneId;                 /**< 注册所属区 ID */
    uint8_t  gameType;               /**< 游戏类型 */
    uint8_t  reserved[3];            /**< 对齐保留 */
};

/**
 * @brief S→C: 注册响应
 *
 * 方向：LoginServer → Client
 * 编号：module=LOGIN(0x00) sub=0x04
 * 触发：C2S_REGISTER_REQ 处理完毕
 */
struct Msg_S2C_RegisterRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_REGISTER_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；1=账号已存在；-1=服务器错误 */
    char     msg[64];                /**< 提示文案 */
    uint64_t accid;                  /**< 账号 ID（成功时有效） */
};

/**
 * @brief S→C: 登录响应
 *
 * 方向：LoginServer → Client
 * 编号：module=LOGIN(0x00) sub=0x02
 * 触发：C2S_LOGIN_REQ 处理完毕；成功时附带 loginToken 供 Gateway 鉴权
 */
struct Msg_S2C_LoginRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_LOGIN_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；1=账号或密码错误；-1=服务器错误 */
    char     msg[64];                /**< 提示文案 */
    uint64_t userID;                 /**< 上次登录角色 ID（0 表示无） */
    uint64_t accid;                  /**< 账号 ID */
    char     loginToken[65];         /**< Gateway 鉴权票据（成功时有效，64 字符 + '\0'） */
    uint64_t tokenExpireMs;          /**< 票据过期时间戳（毫秒，Unix epoch） */
};

/**
 * @brief C→S: Gateway 票据鉴权
 *
 * 方向：Client → GatewayServer（ClientListen）
 * 编号：module=LOGIN(0x00) sub=0x0D
 * 触发：连接 Gateway 后首包，携带 LoginServer 下发的 loginToken
 */
struct Msg_C2S_GatewayAuthReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_GATEWAY_AUTH_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     account[32];            /**< 账号（与登录时一致） */
    char     loginToken[65];         /**< LoginServer 下发的票据 */
    uint32_t zoneId;                 /**< 区服 ID */
    uint8_t  gameType;               /**< 游戏类型 */
    uint8_t  reserved[3];            /**< 对齐保留 */
};

/**
 * @brief S→C: 角色列表头（变长包）
 *
 * 方向：GatewayServer → Client
 * 编号：module=LOGIN(0x00) sub=0x06
 * 触发：Gateway 鉴权成功后主动推送；创角成功后刷新
 *
 * 完整 body = sizeof(Msg_S2C_UserListHeader) + count × sizeof(Msg_S2C_UserListEntryWire)
 */
struct Msg_S2C_UserListHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_USER_LIST);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；-1=服务器错误 */
    uint16_t count;                  /**< 尾随 Msg_S2C_UserListEntryWire 条数 */
};
static_assert(sizeof(Msg_S2C_UserListHeader) == 8,
              "Msg_S2C_UserListHeader must be packed to 8 bytes");

/**
 * @brief C→S: 选角进世界
 *
 * 方向：Client → Gateway → Super → Record/Session/Scene
 * 编号：module=LOGIN(0x00) sub=0x05
 * 触发：Gateway 鉴权通过（ACCOUNT_OK）后选择角色进入游戏
 */
struct Msg_C2S_SelectUserReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_SELECT_USER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;                 /**< 所选角色 ID */
    uint64_t loginTxnId;             /**< 幂等事务 ID（非 0 时 Super 对重复请求静默忽略） */
};

/**
 * @brief C→S: 创建角色
 *
 * 方向：Client → GatewayServer → RecordServer
 * 编号：module=LOGIN(0x00) sub=0x07
 * 触发：Gateway 鉴权通过（ACCOUNT_OK）且角色列表未满时发起创角
 */
struct Msg_C2S_CreateUserReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::C2S_CREATE_USER_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char     name[32];               /**< 角色名（长度见 MIN/MAX_ROLE_NAME_LEN） */
    uint8_t  vocation;               /**< 职业 */
    uint8_t  sex;                    /**< 性别 */
    uint8_t  reserved[2];            /**< 对齐保留 */
};

/**
 * @brief S→C: 创建角色响应
 *
 * 方向：GatewayServer → Client
 * 编号：module=LOGIN(0x00) sub=0x08
 * 触发：C2S_CREATE_USER_REQ 处理完毕；code 见 CreateCharacterError
 */
struct Msg_S2C_CreateUserRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_CREATE_USER_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< CreateCharacterError：0=成功；-1=系统错误；1=重名等 */
    char     msg[64];                /**< 提示文案 */
    uint64_t userID;                 /**< 新角色 ID（成功时有效） */
};

/**
 * @brief S→C: 网关信息
 *
 * 方向：LoginServer → Client
 * 编号：module=LOGIN(0x00) sub=0x0A
 * 触发：登录成功后下发 Gateway 地址，客户端断开 Login 改连 Gateway
 */
struct Msg_S2C_GatewayInfo
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_GATEWAY_INFO);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；-1=无可用网关 */
    char     gatewayIP[32];          /**< 网关 IP 或域名 */
    uint16_t gatewayPort;            /**< 网关端口 */
    char     msg[64];                /**< 提示文案 */
};

/**
 * @brief S→C: 进入游戏世界
 *
 * 方向：Gateway → Client
 * 编号：module=LOGIN(0x00) sub=0x09
 * 触发：选角进世界链路完成，角色已加载并进入场景
 */
struct Msg_S2C_EnterGame
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(LoginMsgSub::S2C_ENTER_GAME);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;                 /**< 角色 ID */
    char     name[32];               /**< 角色名 */
    uint32_t mapID;                  /**< 当前地图 ID */
    float    x, y, z;                /**< 出生坐标 */
    uint32_t level;                  /**< 等级 */
    uint32_t hp;                     /**< 当前生命 */
    uint32_t maxHP;                  /**< 生命上限 */
    uint32_t mp;                     /**< 当前法力 */
    uint32_t maxMP;                  /**< 法力上限 */
};

/**
 * @brief C→S: 心跳
 *
 * 方向：Client → Gateway/Login
 * 编号：module=SYSTEM(0x0F) sub=0x01
 * 触发：定时发送；超时未收到则服务端踢线
 */
struct Msg_C2S_Heartbeat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::C2S_HEARTBEAT);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t seq;                    /**< 客户端序号（原样回显） */
};

/**
 * @brief S→C: 心跳响应
 *
 * 方向：Gateway/Login → Client
 * 编号：module=SYSTEM(0x0F) sub=0x02
 * 触发：收到 C2S_HEARTBEAT 后回复
 */
struct Msg_S2C_Heartbeat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_HEARTBEAT);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t seq;                    /**< 回显客户端 seq */
    uint64_t serverTime;             /**< 服务端当前时间（毫秒，Unix epoch） */
};

/**
 * @brief S→C: 网关校验错误
 *
 * 方向：Gateway → Client
 * 编号：module=SYSTEM(0x0F) sub=0x05
 * 触发：ClientMsgValidator 校验失败
 */
struct Msg_S2C_Error
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_ERROR);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t code;                    /**< GatewayValidateCode */
    char    msg[64];                 /**< 可读提示（可选） */
};

#pragma pack(pop)
