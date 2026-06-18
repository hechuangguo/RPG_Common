/**
 * @file    EquipMsg.h
 * @brief  装备/背包域 wire 消息体（预留）
 *
 * 子编号见 EquipCommon.h；落地时按 LoginMsg.h 模板补充方向/编号/字段注释。
 */

#pragma once
#include "EquipCommon.h"

/*
 * RESERVED — 背包域（module=BAG 0x03）
 *
 * | sub | 名称              | 方向 | 计划 struct           | 处理方      |
 * |-----|-------------------|------|-----------------------|-------------|
 * | 0x01| C2S_BAG_INFO_REQ  | C→S  | Msg_C2S_BagInfoReq    | SceneServer |
 * | 0x02| S2C_BAG_INFO_RSP  | S→C  | Msg_S2C_BagInfoRsp    | SceneServer |
 * | 0x03| C2S_USE_ITEM_REQ  | C→S  | Msg_C2S_UseItemReq    | SceneServer |
 * | 0x04| S2C_USE_ITEM_RSP  | S→C  | Msg_S2C_UseItemRsp    | SceneServer |
 * | 0x05| C2S_DROP_ITEM_REQ | C→S  | Msg_C2S_DropItemReq   | SceneServer |
 */
