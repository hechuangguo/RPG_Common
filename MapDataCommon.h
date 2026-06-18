/**
 * @file    MapDataCommon.h
 * @brief  地图域公共类型：子编号、实体类型、NPC 对话选项等
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstdint>

/** @brief 场景域子编号（module=SCENE） */
enum class SceneMsgSub : uint8_t
{
    C2S_MOVE_REQ       = 0x01,
    S2C_MOVE_NOTIFY    = 0x02,
    S2C_ENTER_MAP      = 0x03,
    S2C_LEAVE_MAP      = 0x04,
    S2C_SPAWN_ENTITY   = 0x05,
    S2C_DESPAWN_ENTITY = 0x06,
    C2S_TELEPORT_REQ   = 0x07,
};

/** @brief NPC 域子编号（module=NPC） */
enum class NpcMsgSub : uint8_t
{
    C2S_NPC_TALK_REQ = 0x01,
    S2C_NPC_TALK_RSP = 0x02,
};

/** @brief 实体类型：玩家 */
constexpr uint8_t ENTITY_TYPE_PLAYER = 0;

/** @brief 实体类型：NPC */
constexpr uint8_t ENTITY_TYPE_NPC = 1;

/** @brief 实体类型：怪物 */
constexpr uint8_t ENTITY_TYPE_MONSTER = 2;

/** @brief 实体类型：宠物 */
constexpr uint8_t ENTITY_TYPE_PET = 3;

/** @brief 实体类型：地面物品 */
constexpr uint8_t ENTITY_TYPE_ITEM = 4;

/** @brief NPC 对话选项最大条数 */
constexpr uint8_t MAX_NPC_TALK_OPTIONS = 4;

/** @brief 移动类型：行走 */
constexpr uint8_t MOVE_TYPE_WALK = 0;

/** @brief 移动类型：跑步 */
constexpr uint8_t MOVE_TYPE_RUN = 1;

#pragma pack(push, 1)

/** @brief 单条 NPC 对话选项 wire 格式 */
struct NpcTalkOptionWire
{
    char    text[64];
    int32_t nextStep;
};

#pragma pack(pop)
