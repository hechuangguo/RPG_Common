/**
 * @file    SpellCommon.h
 * @brief  技能域公共类型（预留）
 */

#pragma once
#include <cstdint>

/** @brief 技能协议预留版本 */
constexpr uint16_t SPELL_PROTOCOL_VERSION = 1;

/** @brief 技能域子编号（module=SKILL） */
enum class SpellMsgSub : uint8_t
{
    C2S_SKILL_REQ    = 0x01,
    S2C_SKILL_NOTIFY = 0x02,
};
