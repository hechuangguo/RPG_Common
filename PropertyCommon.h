/**
 * @file    PropertyCommon.h
 * @brief  角色属性域公共类型（战斗、任务子编号）
 */

#pragma once
#include <cstdint>

/** @brief 战斗/属性协议预留版本 */
constexpr uint16_t PROPERTY_PROTOCOL_VERSION = 1;

/** @brief 战斗域子编号（module=BATTLE） */
enum class BattleMsgSub : uint8_t
{
    C2S_ATTACK_REQ    = 0x01,
    S2C_ATTACK_NOTIFY = 0x02,
    S2C_HP_CHANGE     = 0x03,
    S2C_ENTITY_DIE    = 0x04,
};

/** @brief 任务域子编号（module=QUEST） */
enum class QuestMsgSub : uint8_t
{
    C2S_QUEST_ACCEPT_REQ = 0x01,
    S2C_QUEST_INFO       = 0x02,
    C2S_QUEST_SUBMIT_REQ = 0x03,
    S2C_QUEST_RESULT     = 0x04,
};
