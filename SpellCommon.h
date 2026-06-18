/**
 * @file    SpellCommon.h
 * @brief  技能域公共类型（预留）
 *
 * 对应 ClientModule::SKILL(0x04)。
 * wire 结构体待实现，见 SpellMsg.h RESERVED 块。
 */

#pragma once
#include <cstdint>

/** @brief 技能协议预留版本 */
constexpr uint16_t SPELL_PROTOCOL_VERSION = 1;

/** @brief 技能域子编号（module=SKILL） */
enum class SpellMsgSub : uint8_t
{
    C2S_SKILL_REQ    = 0x01, /**< C→S: 释放技能；计划处理方 SceneServer→Lua */
    S2C_SKILL_NOTIFY = 0x02, /**< S→C: 技能广播；计划处理方 SceneServer */
};
