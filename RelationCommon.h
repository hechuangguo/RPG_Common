/**
 * @file    RelationCommon.h
 * @brief  社会关系域公共类型（好友/队伍/公会，预留）
 *
 * 对应 ClientModule::SOCIAL(0x06)。
 * wire 结构体待实现，见 RelationMsg.h RESERVED 块。
 */

#pragma once
#include <cstdint>

/** @brief 社交域子编号（module=SOCIAL） */
enum class RelationMsgSub : uint8_t
{
    C2S_ADD_FRIEND_REQ  = 0x01, /**< C→S: 加好友；计划处理方 SessionServer */
    S2C_ADD_FRIEND_RSP  = 0x02, /**< S→C: 加好友响应；计划处理方 SessionServer */
    S2C_FRIEND_LIST     = 0x03, /**< S→C: 好友列表；计划处理方 SessionServer */
    C2S_CREATE_TEAM_REQ = 0x10, /**< C→S: 创建队伍；计划处理方 SessionServer */
    S2C_TEAM_INFO       = 0x11, /**< S→C: 队伍信息；计划处理方 SessionServer */
};

/** @brief 好友关系状态：已是好友 */
constexpr uint8_t RELATION_FRIEND_STATUS_OK = 1;

/** @brief 好友关系状态：黑名单 */
constexpr uint8_t RELATION_FRIEND_STATUS_BLACKLIST = 2;
