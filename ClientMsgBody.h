/**
 * @file    ClientMsgBody.h
 * @brief  客户端 wire 消息体公共前缀与初始化/校验工具
 *
 * 线上帧仍为 MsgHeader(6B) + body；body 前两字节与 header module/sub 一致。
 */

#pragma once
#include <cstdint>

/** @brief 协议 BYTE 类型别名 */
using ClientMsgByte = uint8_t;

#pragma pack(push, 1)

/** @brief 所有客户端 wire 消息体公共前缀（2B） */
struct ClientMsgBodyHead
{
    uint8_t module;  /**< ClientModule 指令编号 */
    uint8_t sub;     /**< XxxMsgSub 子编号 */
};

#pragma pack(pop)

/**
 * @brief 构造时写入 struct 默认 module/sub
 * @tparam MsgT 须含 kModule、kSub 及 module、sub 成员
 */
template<typename MsgT>
inline void initClientMsg(MsgT& msg)
{
    msg.module = MsgT::kModule;
    msg.sub    = MsgT::kSub;
}

/**
 * @brief 校验 MsgHeader 与 body 前缀 module/sub 一致
 */
inline bool clientMsgBodyMatches(uint8_t hdrModule, uint8_t hdrSub,
                                 const char* body, uint16_t len)
{
    if (len < sizeof(ClientMsgBodyHead))
        return false;
    const auto* head = reinterpret_cast<const ClientMsgBodyHead*>(body);
    return head->module == hdrModule && head->sub == hdrSub;
}
