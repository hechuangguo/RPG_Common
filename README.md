# RPG_Common

Server 与 Client **共用**的客户端 wire **消息源**（仅 Protobuf `.proto`）。

| 文件 | 说明 |
|------|------|
| `ClientCommon.proto` | 跨域：`ClientModule`、`Vec3`、`ProtocolVersion` |
| `WireCommon.proto` | 4 字节帧常量、`WireMsgHeader`、FlatMsgId 约定 |
| `*Common.proto` | 域内 enum（`XxxMsgSub`、结果码等） |
| `*Msg.proto` | Protobuf wire message |

线上帧：`bodyLen (2B) + module (1B) + sub (1B) + Protobuf body`（body **不含** module/sub 前缀）。

**Server 运行时网络栈**（`MsgHeader` struct、`makeMsgId` 等 C++ helper）在 RPG_Server 主仓 `sdk/net/NetDefine.h`、`sdk/net/MsgId.h`；数值须与 `WireCommon.proto` 一致。

**生成物不在本仓库：**

| 消费方 | 生成目录 | 脚本 |
|--------|----------|------|
| RPG_Server | 主仓 `Protobuf/` | `./scripts/gen_proto.sh` 或 `./Build.sh` |
| Client / Unity | 各自工程内 | 自行从本仓 `.proto` 生成 |

---

## 新增消息 workflow

1. 在 `XxxCommon.proto` 增加 `XxxMsgSub` 子编号
2. 在 `XxxMsg.proto` 定义 message，注释方向与触发时机
3. 新域则在 `ClientCommon.proto` 补 `ClientModule`
4. Server：运行主仓 `./scripts/gen_proto.sh`；Gateway `ClientMsgValidator` + handler
5. Client：自行 `protoc` 生成对应语言代码

---

## 挂载方式（Git Submodule）

| 主仓库 | Submodule 路径 |
|--------|----------------|
| [RPG](https://github.com/hechuangguo/RPG)（Server） | `Common/` |
| [RPG_Client](https://github.com/hechuangguo/RPG_Client)（Client） | `Common/` |

```bash
git submodule update --init --recursive
```

Server 详细文档：[RPG/docs/COMMON.md](https://github.com/hechuangguo/RPG/blob/main/docs/COMMON.md)

---

## 修改协议

1. 在 `Common/` 子模块目录内编辑 `.proto`、`git commit`、`git push origin main`
2. 回到主仓库执行 `./scripts/gen_proto.sh`（或 `./Build.sh`）刷新 `Protobuf/`
3. 主仓库 commit submodule 指针
4. 对方执行 `./pull.sh`

---

## 禁止事项

- **不要**在 Server 或 Client 主仓库内复制一份协议独立维护
- **不要**手改 Server 主仓 `Protobuf/*.pb.*`（AUTO-GENERATED）
- **不要**把服间协议（`InternalMsg.h`）放进本仓库
