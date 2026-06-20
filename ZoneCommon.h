/**
 * @file    ZoneCommon.h
 * @brief  区服/跨区域公共类型：子编号、负载等级、区列表条目、常量与内联工具
 *
 * 区列表子编号挂在 ClientModule::LOGIN(0x00) 下（与登录同连接）。
 * wire 结构体见 ZoneMsg.h。
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstddef>
#include <cstdint>

/** @brief 区服域子编号（module=LOGIN） */
enum class ZoneMsgSub : uint8_t
{
    C2S_ZONE_LIST_REQ = 0x0B, /**< C→S: 请求区列表；处理方 LoginServer */
    S2C_ZONE_LIST_RSP = 0x0C, /**< S→C: 区列表响应（变长）；处理方 LoginServer */
};

/** @brief 区列表响应最大条目数（LoginServer serverlist.xml） */
constexpr uint16_t MAX_ZONE_LIST_ENTRIES = 64;

/**
 * @brief 游戏区负载等级（Msg_S2C_ZoneEntryWire.loadLevel）
 */
enum class ZoneLoadLevel : uint8_t
{
    SMOOTH      = 0, /**< 流畅 */
    BUSY        = 1, /**< 繁忙 */
    FULL        = 2, /**< 爆满（可能禁止新角色） */
    MAINTENANCE = 3, /**< 维护中 */
};

/** @brief 请求全部游戏类型区列表时 gameType 过滤值 */
constexpr uint8_t ZONE_LIST_ALL_GAME_TYPES = 0xFF;

#pragma pack(push, 1)

/**
 * @brief 区列表单条 wire v1 格式（无 onlineCount/loadLevel/gatewayCount）
 *
 * 旧版 LoginServer 变长 body 尾随条目。
 */
struct Msg_S2C_ZoneEntryWireV1
{
    uint32_t zoneId;
    uint8_t  gameType;
    uint8_t  enabled;
    char     name[32];
    char     ip[64];
    uint16_t superPort;
};

/**
 * @brief 区列表单条 wire 格式
 *
 * 变长 body 尾随条目，不含 module/sub 前缀。
 */
struct Msg_S2C_ZoneEntryWire
{
    uint32_t zoneId;        /**< 区 ID */
    uint8_t  gameType;      /**< 游戏类型 */
    uint8_t  enabled;       /**< 1=可进入；0=关闭 */
    char     name[32];      /**< 区名称 */
    char     ip[64];        /**< LoginServer 对外 IP（客户端连此地址） */
    uint16_t superPort;     /**< SuperServer 端口（服间用，客户端一般不用） */
    uint32_t onlineCount;   /**< 当前在线人数 */
    uint8_t  loadLevel;     /**< ZoneLoadLevel */
    uint8_t  gatewayCount;  /**< 该区可用网关数量 */
    uint8_t  reserved[2];   /**< 对齐保留 */
};

#pragma pack(pop)

/**
 * @brief 计算 S2C_ZONE_LIST_RSP body 字节数
 * @param count 区条目数
 * @return sizeof(header 前缀 + code + count) + count × sizeof(ZoneEntryWire)
 */
inline size_t zoneListBodyLen(uint16_t count)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(count) * sizeof(Msg_S2C_ZoneEntryWire);
}
