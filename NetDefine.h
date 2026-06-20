/**
 * @file    NetDefine.h
 * @brief   客户端网络基础定义 —— 消息头、缓冲区常量与连接回调
 *
 * 与 Server 侧 sdk/net/NetDefine.h 字段布局须保持一致。
 */

#pragma once
#include <cstdint>
#include <functional>
#include <string>

/** @brief 单个消息体最大字节数（含 body 内 module/sub 前缀） */
constexpr int MAX_PACKET_SIZE    = 65535;
/** @brief 接收环形缓冲区容量 */
constexpr int RECV_BUFFER_SIZE   = 131072;
/** @brief 发送环形缓冲区容量 */
constexpr int SEND_BUFFER_SIZE   = 131072;
/** @brief epoll_wait 单次最大事件数 */
constexpr int MAX_EPOLL_EVENTS   = 1024;
/** @brief listen 积压队列长度 */
constexpr int LISTEN_BACKLOG     = 512;

/** @brief 连接标识类型 */
using ConnID = uint32_t;
/** @brief 无效连接 ID */
constexpr ConnID INVALID_CONN_ID = 0;

#pragma pack(push, 1)

/**
 * @brief 二进制消息头（定长 6 字节）
 *
 * 线上帧 = MsgHeader + Body；body 前两字节为 module/sub 自描述前缀（见 ClientMsgBody.h）。
 */
struct MsgHeader
{
    uint16_t bodyLen;  /**< 消息体长度（不含本头部；小端 uint16，与 host 一致） */
    uint8_t  module;   /**< ClientModule 指令编号 */
    uint8_t  sub;      /**< 域内 XxxMsgSub 子编号 */
};

#pragma pack(pop)

/** @brief 消息头固定字节数 */
constexpr uint16_t MSG_HEADER_SIZE = sizeof(MsgHeader);

/**
 * @brief 网络层异步事件回调（Client 与 Server 共用抽象）
 */
struct INetCallback
{
    virtual ~INetCallback() = default;

    /** @brief 连接建立 */
    virtual void OnConnect(ConnID id)                                     = 0;

    /** @brief 连接断开 */
    virtual void OnDisconnect(ConnID id)                                  = 0;

    /**
     * @brief 收到完整消息
     * @param module 功能模块号
     * @param sub    子消息号
     * @param data   消息体（含 module/sub 前缀）
     * @param len    消息体长度
     */
    virtual void OnMessage(ConnID id, uint8_t module, uint8_t sub,
                           const char* data, uint16_t len)                = 0;
};
