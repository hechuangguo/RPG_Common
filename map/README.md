# 共享地图数据 (Common/map/)

本目录存放服务器与客户端**共享**的地图几何与逻辑数据。Unity 3D 场景文件 (.scene/.unity) 和美术资源不在此目录，仅在 RPG_Client 仓库 `Assets/` 内。

地图**元数据**（名称、类型、人数上限、版本、出生点等）由 [`../DataDoc/map.xlsx`](../DataDoc/map.xlsx) 维护，服务端打表为 `database/map_config.lua`。

## 目录结构

```
map/
├── {mapId}/
│   ├── meta.json         # 地图元信息（名称、尺寸、version、对应 Unity 场景路径）
│   ├── ambient.json      # **Legacy** 环境 NPC（键值对）；请改用 npc_spawns.json
│   ├── npc_spawns.json   # 环境 NPC（推荐，与 MapExport logic/ 一致）
│   ├── npcs.json         # NPC 详细配置（可选）
│   ├── buildings.json    # 建筑布局
│   ├── collision.json    # **Legacy** 2D 网格碰撞
│   ├── ground.json       # **Legacy** 2D 地面瓦片
│   ├── spawns.json       # 出生点
│   ├── river.json        # 河流（可选）
│   ├── water.json        # 水面参数（可选）
│   └── river_fauna.json  # 水生生物（可选）
```

## 地图清单

| mapId | 名称 | 场景文件 | 说明 |
|-------|------|----------|------|
| 1001 | 新手村 | World_1001.unity | 初始出生点 |
| 1002 | 原野地图 | World_1002.unity | 含河流、建筑 |
| 1003 | 仙侠主城 | MainCity.scene | 铁匠铺、当铺、宠物店、城主府、商店 |

## 各方消费方式

| 消费方 | 读取路径 | 用途 |
|--------|----------|------|
| RPG_Server | `Common/map/{mapId}/*.json` | 碰撞校验、出生点、AOI 边界 |
| RPG_Server | `database/map_config.lua` | 地图元数据、版本交叉校验 |
| RPG_Client | `Common/map/{mapId}/*.json` 或 CDN `client/{mapId}/` | 加载场景、生成 NPC、渲染地图 |

**3D 地图发布**：Unity 场景真源在 RPG_Client；MapExport 产出双端包发布到 CDN。详见 RPG_Client [`docs/RPG_WorldData.md`](../../docs/RPG_WorldData.md)（相对 Client 仓路径）。

客户端通过 `Application.dataPath/../Common/map/{mapId}/` 访问本目录；配置了 `mapCdnBaseUrl` 时优先拉 CDN manifest。

校验：`./tools/map_export/validate_map.sh Common/map`
