/**
 * @file    MapDataCommon.h
 * @brief  地图域公共类型：子编号、实体类型、NPC 对话选项等
 *
 * 对应 ClientModule::SCENE(0x01) 与 ClientModule::NPC(0x08)。
 * wire 结构体见 MapDataMsg.h。
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include <cstdint>

/** @brief 场景域子编号（module=SCENE） */
enum class SceneMsgSub : uint8_t
{
    C2S_MOVE_REQ       = 0x01, /**< C→S: 移动请求；处理方 SceneServer */
    S2C_MOVE_NOTIFY    = 0x02, /**< S→C: 移动广播；处理方 SceneServer（AOI 视野内） */
    S2C_ENTER_MAP      = 0x03, /**< S→C: 进图通知；处理方 SceneServer（wire struct 待实现） */
    S2C_LEAVE_MAP      = 0x04, /**< S→C: 离图通知；处理方 SceneServer（wire struct 待实现） */
    S2C_SPAWN_ENTITY   = 0x05, /**< S→C: 实体进视野；处理方 SceneServer */
    S2C_DESPAWN_ENTITY = 0x06, /**< S→C: 实体出视野；处理方 SceneServer */
    C2S_TELEPORT_REQ   = 0x07, /**< C→S: 传送请求；处理方 SceneServer（wire struct 待实现） */
};

/** @brief NPC 域子编号（module=NPC） */
enum class NpcMsgSub : uint8_t
{
    C2S_NPC_TALK_REQ = 0x01, /**< C→S: NPC 对话请求；处理方 SceneServer→Lua */
    S2C_NPC_TALK_RSP = 0x02, /**< S→C: NPC 对话响应；处理方 SceneServer */
};

/** @brief 实体类型：玩家（Msg_S2C_SpawnEntity.entityType） */
constexpr uint8_t ENTITY_TYPE_PLAYER = 0;

/** @brief 实体类型：NPC */
constexpr uint8_t ENTITY_TYPE_NPC = 1;

/** @brief 实体类型：怪物 */
constexpr uint8_t ENTITY_TYPE_MONSTER = 2;

/** @brief 实体类型：宠物 */
constexpr uint8_t ENTITY_TYPE_PET = 3;

/** @brief 实体类型：地面物品 */
constexpr uint8_t ENTITY_TYPE_ITEM = 4;

/** @brief NPC 对话选项最大条数（Msg_S2C_NpcTalkRsp.options 有效范围） */
constexpr uint8_t MAX_NPC_TALK_OPTIONS = 4;

/** @brief 移动类型：行走（Msg_C2S_MoveReq.moveType） */
constexpr uint8_t MOVE_TYPE_WALK = 0;

/** @brief 移动类型：跑步 */
constexpr uint8_t MOVE_TYPE_RUN = 1;

#pragma pack(push, 1)

/**
 * @brief 单条 NPC 对话选项 wire 格式
 *
 * 嵌入 Msg_S2C_NpcTalkRsp.options[]；有效条数由 optionCount 决定。
 */
struct NpcTalkOptionWire
{
    char    text[64];    /**< 选项显示文案 */
    int32_t nextStep;    /**< 选择后跳转的对话步骤 ID（Lua 脚本约定） */
};

#pragma pack(pop)
