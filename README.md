# RPG_Common

Server 与 Client **共用**的客户端 wire 协议头文件仓库。

| 文件 | 说明 |
|------|------|
| `ClientTypes.h` | `ClientModule` 指令编号（BYTE） |
| `ClientMsgBody.h` | body 前缀、`initClientMsg`、`clientMsgBodyMatches` |
| `XxxCommon.h` | 域内 `XxxMsgSub`、常量、辅助结构 |
| `XxxMsg.h` | wire struct（首字段 `module`/`sub`，含 `kModule`/`kSub`） |
| `NetDefine.h` | 客户端侧 `MsgHeader`（6 字节帧）与缓冲区常量 |
| `MsgId.h` | `makeMsgId` / `clientMsgFlatId` 等工具 |

线上帧：`bodyLen (2B) + module (1B) + sub (1B) + body`；**body 前两字节与头部 module/sub 一致**（wire v2）。

---

## 新增消息 workflow

1. 在 `XxxCommon.h` 增加 `XxxMsgSub : uint8_t` 子编号
2. 在 `XxxMsg.h` 定义 struct：`kModule`/`kSub` + wire 字段 `module`/`sub` 前缀
3. 发送前调用 `initClientMsg(msg)`；`SendMsg(conn, MsgT::kModule, MsgT::kSub, &msg, sizeof(msg))`
4. 若新增域，在 `ClientTypes.h` 补 `ClientModule`

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

1. 在 `Common/` 子模块目录内编辑、`git commit`、`git push origin main`
2. 回到主仓库，`git add Common`，commit submodule 指针并 push
3. 对方执行 `git pull --recurse-submodules`

---

## 禁止事项

- **不要**在 Server 或 Client 主仓库内复制一份协议头独立维护
- **不要**把服间协议（`InternalMsg.h`）放进本仓库
