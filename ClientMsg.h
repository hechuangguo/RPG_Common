/**
 * @file    ClientMsg.h
 * @brief  客户端协议聚合头（已废弃，请按域 include）
 *
 * @deprecated 请改用 ClientTypes.h 与对应 XxxCommon.h / XxxMsg.h。
 *             字段说明、错误码与触发时机均以各域 *Msg.h / *Common.h 为权威定义。
 *             本文件仅保留过渡期兼容，新代码请勿依赖。
 */

#pragma once

#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include "LoginCommon.h"
#include "LoginMsg.h"
#include "ZoneCommon.h"
#include "ZoneMsg.h"
#include "GoldCommon.h"
#include "GoldMsg.h"
#include "RelationCommon.h"
#include "RelationMsg.h"
#include "PropertyCommon.h"
#include "PropertyMsg.h"
#include "SpellCommon.h"
#include "SpellMsg.h"
#include "MapDataCommon.h"
#include "MapDataMsg.h"
#include "ChatCommon.h"
#include "ChatMsg.h"
#include "EquipCommon.h"
#include "EquipMsg.h"
