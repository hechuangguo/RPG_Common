/**
 * @file    ClientMsg.h
 * @brief   【已废弃】客户端协议聚合头 —— 请按域 include XxxMsg.h
 *
 * 本文件仅供 RPG_Client 过渡期兼容；权威定义在各域 *Common.h + *Msg.h。
 * 新代码勿依赖本聚合头，见 Common/Common.txt。
 */

#pragma once

#include "ClientTypes.h"
#include "ClientMsgBody.h"
#include "NetDefine.h"
#include "MsgId.h"

#include "LoginCommon.h"
#include "LoginMsg.h"
#include "ZoneCommon.h"
#include "ZoneMsg.h"
#include "MapDataCommon.h"
#include "MapDataMsg.h"
#include "ChatCommon.h"
#include "ChatMsg.h"
#include "PropertyCommon.h"
#include "PropertyMsg.h"
#include "EquipCommon.h"
#include "EquipMsg.h"
#include "SpellCommon.h"
#include "SpellMsg.h"
#include "RelationCommon.h"
#include "RelationMsg.h"
#include "GoldCommon.h"
#include "GoldMsg.h"
