/**
 * @file    ClientTypes.h
 * @brief  客户端协议全局路由：指令编号 ClientModule
 *
 * 子编号与 wire message 见 Common 下各 .proto（Server C++ 生成物：主仓 Protobuf/）。
 * 线上帧：MsgHeader(6B) + Protobuf body，见 NetDefine.h。
 */

#pragma once
#include <cstdint>

/**
 * @brief 客户端功能模块号（指令编号，BYTE）
 *
 * 子编号索引（Protobuf enum，见对应 *Common.proto）：
 * - rpg.login.LoginMsgSub / rpg.system.SystemMsgSub
 * - rpg.zone.ZoneMsgSub（挂在 LOGIN module）
 * - rpg.mapdata.MapDataMsgSub
 * - rpg.chat.ChatMsgSub
 * - rpg.npc.NpcMsgSub
 * - 0x02–0x07 预留（BATTLE/BAG/SKILL/SOCIAL/QUEST），尚未实现
 */
enum class ClientModule : uint8_t
{
    LOGIN  = 0x00, /**< 登录/注册/选角/区列表；见 LoginCommon.proto、ZoneCommon.proto */
    SCENE  = 0x01, /**< 场景、移动；见 MapDataCommon.proto */
    BATTLE = 0x02, /**< 战斗（未实现） */
    BAG    = 0x03, /**< 背包/物品（未实现） */
    SKILL  = 0x04, /**< 技能（未实现） */
    CHAT   = 0x05, /**< 聊天；见 ChatCommon.proto */
    SOCIAL = 0x06, /**< 社交（未实现） */
    QUEST  = 0x07, /**< 任务（未实现） */
    NPC    = 0x08, /**< NPC 交互；见 NpcCommon.proto */
    SYSTEM = 0x0F, /**< 心跳/踢线/公告/网关错误；见 SystemCommon.proto */
};
