/**
 * @file    MsgId.h
 * @brief  消息 module/sub 与扁平协议号互转
 */

#pragma once
#include <cstdint>

constexpr uint16_t makeMsgId(uint8_t module, uint8_t sub)
{
    return static_cast<uint16_t>((static_cast<uint16_t>(module) << 8) | sub);
}

constexpr uint8_t msgModule(uint16_t flatMsgId)
{
    return static_cast<uint8_t>(flatMsgId >> 8);
}

constexpr uint8_t msgSub(uint16_t flatMsgId)
{
    return static_cast<uint8_t>(flatMsgId & 0xFF);
}

constexpr uint32_t makeMsgKey(uint8_t module, uint8_t sub)
{
    return (static_cast<uint32_t>(module) << 8) | sub;
}

constexpr uint32_t makeMsgKey(uint16_t flatMsgId)
{
    return static_cast<uint32_t>(flatMsgId);
}

/** @brief 从 wire 消息 struct 类型得到扁平协议号（日志/调试） */
template<typename MsgT>
constexpr uint16_t clientMsgFlatId()
{
    return makeMsgId(MsgT::kModule, MsgT::kSub);
}
