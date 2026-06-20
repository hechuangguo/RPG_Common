/**
 * @file    PropertyCommon.h
 * @brief  角色属性域公共类型（战斗、任务子编号）
 *
 * 对应 ClientModule::BATTLE(0x02) 与 ClientModule::QUEST(0x07)。
 * wire 结构体待实现，见 PropertyMsg.h RESERVED 块。
 */

#pragma once
#include "ClientTypes.h"
#include <cstdint>

/** @brief 战斗/属性协议预留版本 */
constexpr uint16_t PROPERTY_PROTOCOL_VERSION = 1;

/** @brief 战斗域子编号（module=BATTLE） */
enum class BattleMsgSub : uint8_t
{
    C2S_ATTACK_REQ    = 0x01, /**< C→S: 普攻请求；计划处理方 SceneServer */
    S2C_ATTACK_NOTIFY = 0x02, /**< S→C: 攻击广播；计划处理方 SceneServer */
    S2C_HP_CHANGE     = 0x03, /**< S→C: 血量变化；计划处理方 SceneServer */
    S2C_ENTITY_DIE    = 0x04, /**< S→C: 实体死亡；计划处理方 SceneServer */
};

/** @brief 任务域子编号（module=QUEST） */
enum class QuestMsgSub : uint8_t
{
    C2S_QUEST_ACCEPT_REQ = 0x01, /**< C→S: 接任务；计划处理方 SessionServer */
    S2C_QUEST_INFO       = 0x02, /**< S→C: 任务同步；计划处理方 SessionServer */
    C2S_QUEST_SUBMIT_REQ = 0x03, /**< C→S: 交任务；计划处理方 SessionServer */
    S2C_QUEST_RESULT     = 0x04, /**< S→C: 任务结果；计划处理方 SessionServer */
};
