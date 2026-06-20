/**
 * @file    EquipMsg.h
 * @brief  装备/背包域 wire 消息体
 */

#pragma once
#include "EquipCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 背包查询
 *
 * 编号：module=BAG(0x03) sub=0x01
 */
struct Msg_C2S_BagInfoReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::BAG);
    static constexpr ClientMsgByte kSub =
        static_cast<ClientMsgByte>(EquipMsgSub::C2S_BAG_INFO_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t userID;
};

/**
 * @brief S→C: 背包数据头（变长包）
 *
 * 完整 body = sizeof(Msg_S2C_BagInfoRspHeader) + slotCount × sizeof(Msg_S2C_BagSlotWire)
 */
struct Msg_S2C_BagInfoRspHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::BAG);
    static constexpr ClientMsgByte kSub =
        static_cast<ClientMsgByte>(EquipMsgSub::S2C_BAG_INFO_RSP);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    uint16_t slotCount;
};
static_assert(sizeof(Msg_S2C_BagInfoRspHeader) == 8,
              "Msg_S2C_BagInfoRspHeader must be packed to 8 bytes");

/**
 * @brief S2C_BAG_INFO_RSP 单格 wire 格式
 */
struct Msg_S2C_BagSlotWire
{
    uint16_t slotIndex;
    uint32_t itemId;
    uint32_t count;
    uint8_t  reserved[2];
};

#pragma pack(pop)

inline size_t bagInfoBodyLen(uint16_t slotCount)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(slotCount) * sizeof(Msg_S2C_BagSlotWire);
}
