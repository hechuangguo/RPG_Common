/**
 * @file    ChatMsg.h
 * @brief  聊天域 wire 消息体（聊天、私聊、系统公告）
 *
 * 子编号见 ChatCommon.h；字段语义以本文件为权威定义。
 */

#pragma once
#include "ChatCommon.h"

#pragma pack(push, 1)

/**
 * @brief C→S: 频道聊天
 *
 * 方向：Client → Gateway → SceneServer
 * 编号：module=CHAT(0x05) sub=0x01
 * 触发：玩家在频道发送消息；channel 见 CHAT_CHANNEL_*
 */
struct Msg_C2S_Chat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::CHAT);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ChatMsgSub::C2S_CHAT_REQ);

    ClientMsgByte module = kModule;  /**< 指令编号，须与 MsgHeader.module 一致 */
    ClientMsgByte sub    = kSub;     /**< 子编号，须与 MsgHeader.sub 一致 */
    uint8_t channel;                 /**< CHAT_CHANNEL_WORLD/ZONE/TEAM/GUILD */
    char    content[MAX_CHAT_CONTENT_LEN]; /**< 聊天内容（UTF-8） */
};

/**
 * @brief S→C: 聊天广播
 *
 * 方向：SceneServer → Gateway → Client（频道内玩家）
 * 编号：module=CHAT(0x05) sub=0x02
 * 触发：某玩家发送聊天后广播给同频道玩家
 */
struct Msg_S2C_Chat
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::CHAT);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(ChatMsgSub::S2C_CHAT_NOTIFY);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    uint64_t fromID;                 /**< 发送者角色 ID */
    char     fromName[32];           /**< 发送者角色名 */
    uint8_t  channel;                /**< 频道 */
    char     content[MAX_CHAT_CONTENT_LEN]; /**< 聊天内容 */
};

/**
 * @brief S→C: 系统公告
 *
 * 方向：Gateway/Scene → Client
 * 编号：module=SYSTEM(0x0F) sub=0x04
 * 触发：GM 或系统定时全服公告
 */
struct Msg_S2C_Notice
{
    static constexpr ClientMsgByte kModule = static_cast<ClientMsgByte>(ClientModule::SYSTEM);
    static constexpr ClientMsgByte kSub    = static_cast<ClientMsgByte>(SystemMsgSub::S2C_NOTICE);

    ClientMsgByte module = kModule;
    ClientMsgByte sub    = kSub;
    char content[MAX_NOTICE_CONTENT_LEN]; /**< 公告正文（UTF-8） */
};

#pragma pack(pop)
