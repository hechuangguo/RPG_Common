/**
 * @file    GoldCommon.h
 * @brief  充值域公共类型（预留，暂无线上 wire 结构）
 */

#pragma once
#include <cstdint>

/** @brief 充值协议预留版本号 */
constexpr uint16_t GOLD_PROTOCOL_VERSION = 1;

/** @brief 充值域子编号（module 待定） */
enum class GoldMsgSub : uint8_t
{
    /* RESERVED */
};
