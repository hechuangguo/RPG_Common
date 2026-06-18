/**
 * @file    RelationMsg.h
 * @brief  社会关系域 wire 消息体（预留）
 *
 * 子编号见 RelationCommon.h；落地时按 LoginMsg.h 模板补充方向/编号/字段注释。
 */

#pragma once
#include "RelationCommon.h"

/*
 * RESERVED — 社交域（module=SOCIAL 0x06）
 *
 * | sub | 名称                | 方向 | 计划 struct             | 处理方        |
 * |-----|---------------------|------|-------------------------|---------------|
 * | 0x01| C2S_ADD_FRIEND_REQ  | C→S  | Msg_C2S_AddFriendReq    | SessionServer |
 * | 0x02| S2C_ADD_FRIEND_RSP  | S→C  | Msg_S2C_AddFriendRsp    | SessionServer |
 * | 0x03| S2C_FRIEND_LIST     | S→C  | Msg_S2C_FriendList      | SessionServer |
 * | 0x10| C2S_CREATE_TEAM_REQ | C→S  | Msg_C2S_CreateTeamReq   | SessionServer |
 * | 0x11| S2C_TEAM_INFO       | S→C  | Msg_S2C_TeamInfo        | SessionServer |
 */
