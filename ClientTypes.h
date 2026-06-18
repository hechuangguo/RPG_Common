/**
 * @file    ClientTypes.h
 * @brief  客户端协议全局路由：指令编号 ClientModule
 *
 * 子编号见各域 XxxMsgSub（*Common.h）；wire 结构体见 *Msg.h。
 * 线上帧：MsgHeader(6B) + body（body 前两字节为 module/sub），见 NetDefine.h。
 */

#pragma once
#include <cstdint>

/**
 * @brief 客户端功能模块号（指令编号，BYTE）
 *
 * 子编号索引：
 * - LoginMsgSub / SystemMsgSub → LoginCommon.h
 * - ZoneMsgSub → ZoneCommon.h
 * - SceneMsgSub / NpcMsgSub → MapDataCommon.h
 * - ChatMsgSub → ChatCommon.h
 * - BattleMsgSub / QuestMsgSub → PropertyCommon.h
 * - EquipMsgSub → EquipCommon.h
 * - SpellMsgSub → SpellCommon.h
 * - RelationMsgSub → RelationCommon.h
 * - GoldMsgSub → GoldCommon.h
 */
enum class ClientModule : uint8_t
{
    LOGIN  = 0x00, /**< 登录/注册/选角；见 LoginMsg.h */
    SCENE  = 0x01, /**< 场景、移动；见 MapDataMsg.h */
    BATTLE = 0x02, /**< 战斗；见 PropertyMsg.h */
    BAG    = 0x03, /**< 背包/物品；见 EquipMsg.h */
    SKILL  = 0x04, /**< 技能；见 SpellMsg.h */
    CHAT   = 0x05, /**< 聊天；见 ChatMsg.h */
    SOCIAL = 0x06, /**< 社交；见 RelationMsg.h */
    QUEST  = 0x07, /**< 任务；见 PropertyMsg.h */
    NPC    = 0x08, /**< NPC 交互；见 MapDataMsg.h */
    SYSTEM = 0x0F, /**< 心跳/踢线/公告/网关错误；见 LoginMsg.h、ChatMsg.h */
};
