# AI Infra 学习记录

这里记录 [32 周学习计划](AI集群互连-32周逐日学习计划-AI-Infra补强版.html) 的学习过程：每天的实践写进日记，可复用的知识整理进文档，代码放在能独立运行的练习、实验或项目中。计划 HTML 的勾选进度保存在当前浏览器，不随 Git 仓库同步。

## 从这里开始

| 内容 | 入口 |
| --- | --- |
| 每日记录 | [journal/](journal/)；最近记录：[9 月 27 日](journal/2026-09-27.md)、[9 月 28 日](journal/2026-09-28.md) |
| 主题笔记 | [docs/](docs/)，目前有 [CSAPP 第 2 章](docs/csapp/ch02.md) 与 [环境配置](docs/setup/environment.md) |
| C 小练习 | [exercises/](exercises/)：字节布局、指针、结构体对齐 |
| CSAPP 实验 | [Data Lab](labs/csapp/datalab/README.md) 和 [Bomb Lab](labs/csapp/bomblab/README.md) |
| 跨周项目 | [projects/](projects/)；项目开始时建立独立目录 |

## 学习阶段与产出位置

| 阶段 | 周次 | 主要产出 | 归档位置 |
| --- | --- | --- | --- |
| P0：C 与系统基础 | W1–W6 | CSAPP 实验、C 小练习、高并发服务器 | `labs/csapp/`、`exercises/c/`、`projects/high-perf-server/` |
| P1：网络与 RDMA | W7–W15 | 抓包与协议笔记、Verbs 程序、性能对照 | `docs/networking/`、`docs/rdma/`、`projects/rdma-benchmark/` |
| P2：GPU、NCCL 与训练 | W16–W23 | 源码图、基准数据、可复现的训练通信主项目 | `docs/gpu/`、`docs/collectives/`、`projects/training-communication/` |
| P3：面试与实习 | W24–W32 | 技术复盘与可展示的项目证据 | `docs/interview/`、各项目的 `README.md` 与 `results/` |

未来的目录在开始对应任务时再创建。日记保存过程和问题；`docs/` 保存按主题整理、可反复查阅的结论；实验包保持原有文件结构；项目的代码、运行说明和实测结果放在同一个项目目录。

## 已有练习与实验

- [字节布局](exercises/c/byte_layout.c)：观察 C 对象与地址。
- [指针练习](exercises/c/pointer_drills.c)：含待完成的练习，不能当作已完成答案。
- [结构体布局实验](exercises/c/sep25_layout_lab.c)：用 `sizeof`、`_Alignof`、`offsetof` 验证大小与对齐。
- [Data Lab](labs/csapp/datalab/README.md)：实验包与测试说明。
- [Bomb Lab](labs/csapp/bomblab/README.md)：程序与调试入口。

在仓库根目录运行结构体布局实验：

```sh
mkdir -p build
gcc -std=c11 -g -O0 -Wall -Wextra exercises/c/sep25_layout_lab.c -o build/sep25_layout_lab
./build/sep25_layout_lab
```

`build/` 中的生成文件不纳入版本管理。实验包自带的可执行工具留在各自的 `handout/` 中。后续每个实验或项目的 README 应记录环境、构建与运行命令、真实测试结果及未验证的部分；性能结果连同硬件和版本信息存放在对应项目的 `results/`。
