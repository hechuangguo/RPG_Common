/**
 * @file    PropertyMsg.h
 * @brief  角色属性域 wire 消息体（战斗、任务；子编号已登记，struct 待实现）
 *
 * 子编号见 PropertyCommon.h；落地时按 LoginMsg.h 模板补充方向/编号/字段注释。
 */

#pragma once
#include "PropertyCommon.h"

/*
 * RESERVED — 战斗域（module=BATTLE 0x02）
 *
 * | sub | 名称              | 方向 | 计划 struct           | 处理方      |
 * |-----|-------------------|------|-----------------------|-------------|
 * | 0x01| C2S_ATTACK_REQ    | C→S  | Msg_C2S_AttackReq     | SceneServer |
 * | 0x02| S2C_ATTACK_NOTIFY | S→C  | Msg_S2C_AttackNotify  | SceneServer |
 * | 0x03| S2C_HP_CHANGE     | S→C  | Msg_S2C_HpChange      | SceneServer |
 * | 0x04| S2C_ENTITY_DIE    | S→C  | Msg_S2C_EntityDie     | SceneServer |
 *
 * RESERVED — 任务域（module=QUEST 0x07）
 *
 * | sub | 名称                 | 方向 | 计划 struct              | 处理方        |
 * |-----|----------------------|------|--------------------------|---------------|
 * | 0x01| C2S_QUEST_ACCEPT_REQ | C→S  | Msg_C2S_QuestAcceptReq   | SessionServer |
 * | 0x02| S2C_QUEST_INFO       | S→C  | Msg_S2C_QuestInfo        | SessionServer |
 * | 0x03| C2S_QUEST_SUBMIT_REQ | C→S  | Msg_C2S_QuestSubmitReq   | SessionServer |
 * | 0x04| S2C_QUEST_RESULT     | S→C  | Msg_S2C_QuestResult      | SessionServer |
 */
