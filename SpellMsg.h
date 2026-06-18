/**
 * @file    SpellMsg.h
 * @brief  技能域 wire 消息体（预留）
 *
 * 子编号见 SpellCommon.h；落地时按 LoginMsg.h 模板补充方向/编号/字段注释。
 */

#pragma once
#include "SpellCommon.h"

/*
 * RESERVED — 技能域（module=SKILL 0x04）
 *
 * | sub | 名称              | 方向 | 计划 struct           | 处理方      |
 * |-----|-------------------|------|-----------------------|-------------|
 * | 0x01| C2S_SKILL_REQ     | C→S  | Msg_C2S_SkillReq      | SceneServer |
 * | 0x02| S2C_SKILL_NOTIFY  | S→C  | Msg_S2C_SkillNotify   | SceneServer |
 */
