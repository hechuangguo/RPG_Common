/**
 * @file    ChatCommon.h
 * @brief  聊天域公共类型：子编号、频道常量等
 */

#pragma once
#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include "LoginCommon.h"
#include <cstdint>

/** @brief 聊天域子编号（module=CHAT） */
enum class ChatMsgSub : uint8_t
{
    C2S_CHAT_REQ       = 0x01,
    S2C_CHAT_NOTIFY    = 0x02,
    C2S_WHISPER_REQ    = 0x03,
    S2C_WHISPER_NOTIFY = 0x04,
};

/** @brief 聊天频道：世界 */
constexpr uint8_t CHAT_CHANNEL_WORLD = 0;

/** @brief 聊天频道：区域 */
constexpr uint8_t CHAT_CHANNEL_ZONE = 1;

/** @brief 聊天频道：队伍 */
constexpr uint8_t CHAT_CHANNEL_TEAM = 2;

/** @brief 聊天频道：公会 */
constexpr uint8_t CHAT_CHANNEL_GUILD = 3;

/** @brief 聊天内容最大字节数（UTF-8） */
constexpr uint32_t MAX_CHAT_CONTENT_LEN = 256;

/** @brief 系统公告内容最大字节数 */
constexpr uint32_t MAX_NOTICE_CONTENT_LEN = 512;
