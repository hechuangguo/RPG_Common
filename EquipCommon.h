/**
 * @file    EquipCommon.h
 * @brief  装备/背包域公共类型（预留）
 *
 * 对应 ClientModule::BAG(0x03)。
 * wire 结构体待实现，见 EquipMsg.h RESERVED 块。
 */

#pragma once
#include "ClientTypes.h"
#include <cstdint>

/** @brief 背包槽位上限（策划表对齐前占位） */
constexpr uint16_t MAX_BAG_SLOTS = 64;

/** @brief 背包域子编号（module=BAG） */
enum class EquipMsgSub : uint8_t
{
    C2S_BAG_INFO_REQ  = 0x01, /**< C→S: 背包查询；计划处理方 SceneServer */
    S2C_BAG_INFO_RSP  = 0x02, /**< S→C: 背包数据；计划处理方 SceneServer */
    C2S_USE_ITEM_REQ  = 0x03, /**< C→S: 使用物品；计划处理方 SceneServer→Lua */
    S2C_USE_ITEM_RSP  = 0x04, /**< S→C: 使用结果；计划处理方 SceneServer */
    C2S_DROP_ITEM_REQ = 0x05, /**< C→S: 丢弃物品；计划处理方 SceneServer */
};
