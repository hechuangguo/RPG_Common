# RPG_Common

Server 与 Client **共用**的客户端 wire 协议头文件仓库。

| 文件 | 说明 |
|------|------|
| `ClientMsg.h` | `ClientModule`、`ClientMsgID`、`Msg_C2S_*` / `Msg_S2C_*` |
| `NetDefine.h` | 客户端侧 `MsgHeader`（6 字节帧）与缓冲区常量 |
| `MsgId.h` | `makeMsgId` / `msgModule` / `msgSub` |

线上帧：`bodyLen (2B) + module (1B) + sub (1B) + body`。

---

## 挂载方式（Git Submodule）

| 主仓库 | Submodule 路径 |
|--------|----------------|
| [RPG](https://github.com/hechuangguo/RPG)（Server） | `Common/` |
| [RPG_Client](https://github.com/hechuangguo/RPG_Client)（Client） | `Common/` |

```bash
# 已配置 .gitmodules 的仓库
git submodule update --init --recursive

# Client 仓库首次添加
git submodule add -b main https://github.com/hechuangguo/RPG_Common.git Common
```

Server 详细文档：[RPG/docs/COMMON.md](https://github.com/hechuangguo/RPG/blob/main/docs/COMMON.md)

---

## 修改协议

1. 在 `Common/` 子模块目录内编辑、`git commit`、`git push origin main`（推到 **本仓库** RPG_Common）
2. 回到主仓库（RPG 或 RPG_Client），`git add Common`，commit submodule 指针并 push
3. 对方执行 `git pull --recurse-submodules`

```bash
cd Common
git checkout main
# 编辑 ClientMsg.h 等
git add . && git commit -m "feat(protocol): ..."
git push origin main
cd ..
git add Common && git commit -m "chore: bump Common" && git push
```

---

## 禁止事项

- **不要**在 Server 或 Client 主仓库内复制一份 `ClientMsg.h` 独立维护
- **不要**把服间协议（`InternalMsg.h`）放进本仓库；服间协议仅属于 Server 仓库

---

## 相关链接

- 仓库：https://github.com/hechuangguo/RPG_Common
- Server 协议参考：https://github.com/hechuangguo/RPG/blob/main/docs/PROTOCOL.md
