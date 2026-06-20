/**
 * @file    PropertyMsg.h
 * @brief  角色属性域 wire 消息体（任务；战斗 struct 仍预留）
 */

#pragma once
#include "PropertyCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 接任务
 *
 * 编号：module=QUEST(0x07) sub=0x01
 */
struct Msg_C2S_QuestAcceptReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::QUEST);
    static constexpr ClientMsgByte kSub =
        static_cast<ClientMsgByte>(QuestMsgSub::C2S_QUEST_ACCEPT_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t questId;
};

/**
 * @brief C→S: 交任务
 *
 * 编号：module=QUEST(0x07) sub=0x03
 */
struct Msg_C2S_QuestSubmitReq
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::QUEST);
    static constexpr ClientMsgByte kSub =
        static_cast<ClientMsgByte>(QuestMsgSub::C2S_QUEST_SUBMIT_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint32_t questId;
};

/**
 * @brief S→C: 任务同步头（变长包）
 *
 * 完整 body = sizeof(Msg_S2C_QuestInfoHeader) + count × sizeof(Msg_S2C_QuestEntryWire)
 */
struct Msg_S2C_QuestInfoHeader
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::QUEST);
    static constexpr ClientMsgByte kSub =
        static_cast<ClientMsgByte>(QuestMsgSub::S2C_QUEST_INFO);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    int32_t  code;
    uint16_t count;
};
static_assert(sizeof(Msg_S2C_QuestInfoHeader) == 8,
              "Msg_S2C_QuestInfoHeader must be packed to 8 bytes");

/**
 * @brief S2C_QUEST_INFO 单条任务 wire 格式
 */
struct Msg_S2C_QuestEntryWire
{
    uint32_t questId;
    char     name[32];
    uint32_t progress;
    uint32_t target;
    uint8_t  done;
    uint8_t  reserved[3];
};

#pragma pack(pop)

inline size_t questInfoBodyLen(uint16_t count)
{
    constexpr size_t kHeaderBytes = sizeof(ClientMsgBodyHead) + sizeof(int32_t) + sizeof(uint16_t);
    return kHeaderBytes + static_cast<size_t>(count) * sizeof(Msg_S2C_QuestEntryWire);
}
