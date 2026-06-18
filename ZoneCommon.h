/**
 * @file    ZoneCommon.h
 * @brief  区服/跨区域公共类型：子编号、负载等级、区列表条目、常量与内联工具
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstddef>
#include <cstdint>

/** @brief 区服域子编号（module=LOGIN） */
enum class ZoneMsgSub : uint8_t
{
    C2S_ZONE_LIST_REQ = 0x0B,
    S2C_ZONE_LIST_RSP = 0x0C,
};

/** @brief 区列表响应最大条目数（LoginServer serverlist.xml） */
constexpr uint16_t MAX_ZONE_LIST_ENTRIES = 64;

/**
 * @brief 游戏区负载等级（S2C_ZONE_LIST_RSP 单条 loadLevel 字段）
 */
enum class ZoneLoadLevel : uint8_t
{
    SMOOTH      = 0,
    BUSY        = 1,
    FULL        = 2,
    MAINTENANCE = 3,
};

/** @brief 请求全部游戏类型区列表时 gameType 过滤值 */
constexpr uint8_t ZONE_LIST_ALL_GAME_TYPES = 0xFF;

#pragma pack(push, 1)

/** @brief S→C: 区列表单条 wire 格式（无 module/sub） */
struct Msg_S2C_ZoneEntryWire
{
    uint32_t zoneId;
    uint8_t  gameType;
    uint8_t  enabled;
    char     name[32];
    char     ip[64];
    uint16_t superPort;
    uint32_t onlineCount;
    uint8_t  loadLevel;
    uint8_t  gatewayCount;
    uint8_t  reserved[2];
};

#pragma pack(pop)

/** @brief 计算 S2C_ZONE_LIST_RSP body 字节数（含 header 前缀 + entries） */
inline size_t zoneListBodyLen(uint16_t count)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(count) * sizeof(Msg_S2C_ZoneEntryWire);
}
