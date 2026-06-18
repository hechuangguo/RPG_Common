/**
 * @file    MapDataMsg.h
 * @brief  地图域 wire 消息体（移动、视野实体、NPC 对话）
 *
 * 子编号见 MapDataCommon.h；字段语义以本文件为权威定义。
 */

#pragma once
#include "MapDataCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 移动请求
 *
 * 方向：Client → Gateway → SceneServer
 * 编号：module=SCENE(0x01) sub=0x01
 * 触发：玩家操作移动；Scene 校验后转发 AOI 广播
 */
struct Msg_C2S_MoveReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::C2S_MOVE_REQ);

    ClientMsgByte module = kModule;  /**< 指令编号，须与 MsgHeader.module 一致 */
    ClientMsgByte sub    = kSub;     /**< 子编号，须与 MsgHeader.sub 一致 */
    uint64_t userID;                 /**< 移动者角色 ID */
    float    x, y, z;                /**< 目标世界坐标 */
    float    dir;                    /**< 朝向（弧度或度，客户端约定） */
    uint8_t  moveType;               /**< MOVE_TYPE_WALK 或 MOVE_TYPE_RUN */
};

/**
 * @brief S→C: 移动广播
 *
 * 方向：SceneServer → Gateway → Client（AOI 视野内玩家）
 * 编号：module=SCENE(0x01) sub=0x02
 * 触发：某玩家移动经 AOI 同步给周围玩家
 */
struct Msg_S2C_MoveNotify
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_MOVE_NOTIFY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;                 /**< 移动者实体 ID */
    float    x, y, z;                /**< 当前坐标 */
    float    dir;                    /**< 朝向 */
    uint8_t  moveType;               /**< 移动类型 */
};

/**
 * @brief S→C: 实体进视野
 *
 * 方向：SceneServer → Gateway → Client
 * 编号：module=SCENE(0x01) sub=0x05
 * 触发：AOI 通知某实体进入观察者视野
 *
 * entityType 取值：
 * - 0 PLAYER  — 玩家
 * - 1 NPC     — NPC
 * - 2 MONSTER — 怪物
 * - 3 PET     — 宠物
 * - 4 ITEM    — 地面物品
 */
struct Msg_S2C_SpawnEntity
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_SPAWN_ENTITY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t entityID;               /**< 实体唯一 ID */
    char     name[32];               /**< 显示名（玩家角色名或模板名） */
    uint32_t level;                  /**< 等级（NPC/怪物有意义） */
    float    x, y, z;                /**< 世界坐标 */
    float    dir;                    /**< 朝向 */
    uint8_t  entityType;             /**< ENTITY_TYPE_* 常量 */
};

/**
 * @brief S→C: 实体出视野
 *
 * 方向：SceneServer → Gateway → Client
 * 编号：module=SCENE(0x01) sub=0x06
 * 触发：AOI 通知某实体离开观察者视野或下线
 */
struct Msg_S2C_DespawnEntity
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SCENE);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SceneMsgSub::S2C_DESPAWN_ENTITY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t entityID;               /**< 离开视野的实体 ID */
};

/**
 * @brief C→S: NPC 对话请求
 *
 * 方向：Client → Gateway → SceneServer → Lua
 * 编号：module=NPC(0x08) sub=0x01
 * 触发：玩家点击 NPC 或选择对话选项
 */
struct Msg_C2S_NpcTalkReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::NPC);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(NpcMsgSub::C2S_NPC_TALK_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t npcId;                  /**< 目标 NPC 实体 ID */
    int32_t  dialogStep;             /**< 当前对话步骤（0 表示开场） */
};

/**
 * @brief S→C: NPC 对话响应
 *
 * 方向：SceneServer → Gateway → Client
 * 编号：module=NPC(0x08) sub=0x02
 * 触发：Lua 脚本返回对话内容与选项
 *
 * optionCount 有效范围 0～MAX_NPC_TALK_OPTIONS；仅 options[0..optionCount-1] 有效。
 */
struct Msg_S2C_NpcTalkRsp
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::NPC);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(NpcMsgSub::S2C_NPC_TALK_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；非 0 为脚本或校验错误 */
    uint64_t npcId;                  /**< 对话 NPC 实体 ID */
    int32_t  dialogStep;             /**< 当前对话步骤 ID */
    char     text[256];              /**< 对话正文 */
    uint8_t  optionCount;            /**< 有效选项数（≤ MAX_NPC_TALK_OPTIONS） */
    NpcTalkOptionWire options[MAX_NPC_TALK_OPTIONS]; /**< 对话选项列表 */
};

#pragma pack(pop)
