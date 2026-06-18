/**
 * @file    EquipCommon.h
 * @brief  装备/背包域公共类型（预留）
 */

#pragma once
#include <cstdint>

/** @brief 背包槽位上限（策划表对齐前占位） */
constexpr uint16_t MAX_BAG_SLOTS = 64;

/** @brief 背包域子编号（module=BAG） */
enum class EquipMsgSub : uint8_t
{
    C2S_BAG_INFO_REQ  = 0x01,
    S2C_BAG_INFO_RSP  = 0x02,
    C2S_USE_ITEM_REQ  = 0x03,
    S2C_USE_ITEM_RSP  = 0x04,
    C2S_DROP_ITEM_REQ = 0x05,
};
