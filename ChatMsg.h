/**
 * @file    ChatMsg.h
 * @brief  聊天域 wire 消息体（聊天、私聊、系统公告）
 */

#pragma once
#include "ChatCommon.h"

#pragma pack(push, 1)

/** @brief C→S 聊天；module=CHAT(0x05) sub=0x01 */
struct Msg_C2S_Chat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::CHAT);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ChatMsgSub::C2S_CHAT_REQ);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint8_t channel;
    char    content[MAX_CHAT_CONTENT_LEN];
};

/** @brief S→C 聊天广播；module=CHAT(0x05) sub=0x02 */
struct Msg_S2C_Chat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::CHAT);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ChatMsgSub::S2C_CHAT_NOTIFY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t fromID;
    char     fromName[32];
    uint8_t  channel;
    char     content[MAX_CHAT_CONTENT_LEN];
};

/** @brief S→C 系统公告；module=SYSTEM(0x0F) sub=0x04 */
struct Msg_S2C_Notice
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_NOTICE);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char content[MAX_NOTICE_CONTENT_LEN];
};

#pragma pack(pop)
