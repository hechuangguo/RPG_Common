# 共享地图数据 (Common/map/)

本目录存放服务器与客户端**共享**的地图逻辑数据。Unity 3D 场景文件 (.scene/.unity) 和美术资源不在此目录，仅在 RPG_Client 仓库 `Assets/` 内。

## 目录结构

```
map/
├── {mapId}/
│   ├── meta.json         # 地图元信息（名称、尺寸、对应 Unity 场景路径）
│   ├── ambient.json      # 环境NPC配置（类型+数量，向后兼容）
│   ├── npcs.json         # NPC详细配置（可选，替代 ambient.json）
│   ├── buildings.json    # 建筑布局
│   ├── collision.json    # 碰撞体定义
│   ├── ground.json       # 地面配置
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
| RPG_Server | `Common/map/{mapId}/*.json` | 碰撞校验、NPC管理、出生点 |
| RPG_Client | `Common/map/{mapId}/*.json` | 加载场景、生成NPC、渲染地图 |

客户端通过 `Application.dataPath/../Common/map/{mapId}/` 访问本目录。
