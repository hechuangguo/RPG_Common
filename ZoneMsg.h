/**
 * @file    ZoneMsg.h
 * @brief  区服域 wire 消息体（区列表；跨区消息预留）
 */

#pragma once
#include "ZoneCommon.h"

#pragma pack(push, 1)

/** @brief C→S 区列表请求；module=LOGIN(0x00) sub=0x0B */
struct Msg_C2S_ZoneListReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ZoneMsgSub::C2S_ZONE_LIST_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint8_t gameType;
};

/** @brief S→C 区列表响应头；module=LOGIN(0x00) sub=0x0C */
struct Msg_S2C_ZoneListRspHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::LOGIN);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ZoneMsgSub::S2C_ZONE_LIST_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    uint16_t count;
};
static_assert(sizeof(Msg_S2C_ZoneListRspHeader) == 8,
              "Msg_S2C_ZoneListRspHeader must be packed to 8 bytes");

#pragma pack(pop)

/* 跨区协议预留：后续在 ZoneMsg.h 追加 Msg_C2S_CrossZone_* / Msg_S2C_CrossZone_* */
