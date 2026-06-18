/**
 * @file    GoldMsg.h
 * @brief  充值域 wire 消息体（预留）
 *
 * 子编号见 GoldCommon.h；落地时按 LoginMsg.h 模板补充方向/编号/字段注释。
 */

#pragma once
#include "GoldCommon.h"

/*
 * RESERVED — 充值域（module 待定）
 *
 * | sub | 名称              | 方向 | 计划 struct           | 处理方      |
 * |-----|-------------------|------|-----------------------|-------------|
 * | TBD | C2S_RECHARGE_REQ  | C→S  | Msg_C2S_RechargeReq   | LoginServer |
 * | TBD | S2C_RECHARGE_RSP  | S→C  | Msg_S2C_RechargeRsp   | LoginServer |
 *
 * 服间充值消息见 protocal/InternalMsg.h LOGIN_RECHARGE 系列。
 */
