/**
 * @file    MsgId.h
 * @brief  消息 module/sub 与扁平协议号互转
 *
 * 扁平 ID = (module << 8) | sub，仅用于日志、调试与 SendMsg(uint16_t) 重载。
 */

#pragma once
#include <cstdint>

/** @brief 由 module/sub 合成扁平协议号 */
constexpr uint16_t makeMsgId(uint8_t module, uint8_t sub)
{
    return static_cast<uint16_t>((static_cast<uint16_t>(module) << 8) | sub);
}

/** @brief 从扁平协议号取 module（高字节） */
constexpr uint8_t msgModule(uint16_t flatMsgId)
{
    return static_cast<uint8_t>(flatMsgId >> 8);
}

/** @brief 从扁平协议号取 sub（低字节） */
constexpr uint8_t msgSub(uint16_t flatMsgId)
{
    return static_cast<uint8_t>(flatMsgId & 0xFF);
}

/** @brief 合成 32 位路由键（module 在高 8 位） */
constexpr uint32_t makeMsgKey(uint8_t module, uint8_t sub)
{
    return (static_cast<uint32_t>(module) << 8) | sub;
}

/** @brief 由扁平协议号得到 32 位路由键 */
constexpr uint32_t makeMsgKey(uint16_t flatMsgId)
{
    return static_cast<uint32_t>(flatMsgId);
}

/**
 * @brief 从 wire 消息 struct 类型得到扁平协议号
 * @tparam MsgT 须含 kModule、kSub 静态常量
 * @return makeMsgId(MsgT::kModule, MsgT::kSub)
 */
template<typename MsgT>
constexpr uint16_t clientMsgFlatId()
{
    return makeMsgId(MsgT::kModule, MsgT::kSub);
}
