/**
 * @file    ZoneMsg.h
 * @brief  区服域 wire 消息体（区列表；跨区消息预留）
 *
 * 子编号见 ZoneCommon.h；字段语义以本文件为权威定义。
 */

#pragma once
#include "ZoneCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 区列表请求
 *
 * 方向：Client → LoginServer
 * 编号：module=LOGIN(0x00) sub=0x0B
 * 触发：登录界面前或切换区时拉取可选区服
 */
struct Msg_C2S_ZoneListReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ZoneMsgSub::C2S_ZONE_LIST_REQ);

    ClientMsgByte module = kModule;  /**< 指令编号，须与 MsgHeader.module 一致 */
    ClientMsgByte sub    = kSub;     /**< 子编号，须与 MsgHeader.sub 一致 */
    uint8_t gameType;                /**< 游戏类型过滤；ZONE_LIST_ALL_GAME_TYPES 表示全部 */
};

/**
 * @brief S→C: 区列表响应头（变长包）
 *
 * 方向：LoginServer → Client
 * 编号：module=LOGIN(0x00) sub=0x0C
 * 触发：C2S_ZONE_LIST_REQ 处理完毕
 *
 * 完整 body = sizeof(Msg_S2C_ZoneListRspHeader) + count × sizeof(Msg_S2C_ZoneEntryWire)
 */
struct Msg_S2C_ZoneListRspHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ZoneMsgSub::S2C_ZONE_LIST_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;                   /**< 0=成功；-1=服务器错误 */
    uint16_t count;                  /**< 尾随 Msg_S2C_ZoneEntryWire 条数（≤ MAX_ZONE_LIST_ENTRIES） */
};
static_assert(sizeof(Msg_S2C_ZoneListRspHeader) == 8,
              "Msg_S2C_ZoneListRspHeader must be packed to 8 bytes");

#pragma pack(pop)

/* 跨区协议预留：后续在 ZoneMsg.h 追加 Msg_C2S_CrossZone_* / Msg_S2C_CrossZone_* */
