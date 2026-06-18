/**
 * @file    MapDataMsg.h
 * @brief  地图域 wire 消息体（移动、视野实体、NPC 对话）
 */

#pragma once
#include "MapDataCommon.h"

#pragma pack(push, 1)

/** @brief C→S 移动；module=SCENE(0x01) sub=0x01 */
struct Msg_C2S_MoveReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::C2S_MOVE_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;
    float    x, y, z;
    float    dir;
    uint8_t  moveType;
};

/** @brief S→C 移动广播；module=SCENE(0x01) sub=0x02 */
struct Msg_S2C_MoveNotify
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_MOVE_NOTIFY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;
    float    x, y, z;
    float    dir;
    uint8_t  moveType;
};

/** @brief S→C 实体进视野；module=SCENE(0x01) sub=0x05 */
struct Msg_S2C_SpawnEntity
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_SPAWN_ENTITY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t entityID;
    char     name[32];
    uint32_t level;
    float    x, y, z;
    float    dir;
    uint8_t  entityType;
};

/** @brief S→C 实体出视野；module=SCENE(0x01) sub=0x06 */
struct Msg_S2C_DespawnEntity
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_DESPAWN_ENTITY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t entityID;
};

/** @brief C→S NPC 对话；module=NPC(0x08) sub=0x01 */
struct Msg_C2S_NpcTalkReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::NPC);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(NpcMsgSub::C2S_NPC_TALK_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t npcId;
    int32_t  dialogStep;
};

/** @brief S→C NPC 对话；module=NPC(0x08) sub=0x02 */
struct Msg_S2C_NpcTalkRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::NPC);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(NpcMsgSub::S2C_NPC_TALK_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    uint64_t npcId;
    int32_t  dialogStep;
    char     text[256];
    uint8_t  optionCount;
    NpcTalkOptionWire options[MAX_NPC_TALK_OPTIONS];
};

#pragma pack(pop)
