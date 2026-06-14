/**
 * @file    NetDefine.h
 * @brief   客户端网络基础定义 —— 消息头与常量
 */

#pragma once
#include <cstdint>
#include <functional>
#include <string>

constexpr int MAX_PACKET_SIZE    = 65535;
constexpr int RECV_BUFFER_SIZE   = 131072;
constexpr int SEND_BUFFER_SIZE   = 131072;
constexpr int MAX_EPOLL_EVENTS   = 1024;
constexpr int LISTEN_BACKLOG     = 512;

using ConnID = uint32_t;
constexpr ConnID INVALID_CONN_ID = 0;

#pragma pack(push, 1)

struct MsgHeader
{
    uint16_t bodyLen;
    uint8_t  module;
    uint8_t  sub;
};

#pragma pack(pop)

constexpr uint16_t MSG_HEADER_SIZE = sizeof(MsgHeader);

struct INetCallback
{
    virtual ~INetCallback() = default;

    virtual void OnConnect(ConnID id)                                     = 0;
    virtual void OnDisconnect(ConnID id)                                  = 0;
    virtual void OnMessage(ConnID id, uint8_t module, uint8_t sub,
                           const char* data, uint16_t len)                = 0;
};
