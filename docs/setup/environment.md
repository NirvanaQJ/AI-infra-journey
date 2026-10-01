# W1 环境配置记录

完成日期：2026-09-19

## 系统
- 发行版：Ubuntu 26.04.1 LTS
- 内核：7.0.0-31-generic

## 工具链版本
- gcc: gcc (Ubuntu 15.2.0-16ubuntu1) 15.2.0
- gdb: GNU gdb (Ubuntu 17.1-2ubuntu1) 17.1
- make: GNU Make 4.4.1
- cmake: cmake version 4.2.3
- git: git version 2.53.0

## GitHub 通道
- 账号：NirvanaQJ
- 走的 ssh.github.com:443（22 端口被校园网封锁，已改道）

## 踩坑记录
- 现象：ssh -T git@github.com 报 Connection refused port 22
- 原因：校园网/运营商封锁 22 端口出站
- 解法：~/.ssh/config 加 HostName ssh.github.com + Port 443

## 待验证清单（后续补齐）
- [ ] sudo modprobe rdma_rxe —— W12 前必须通
- [ ] nvidia-smi —— W16 CUDA 前必须通
- [ ] perf stat ls —— W6 后常用
