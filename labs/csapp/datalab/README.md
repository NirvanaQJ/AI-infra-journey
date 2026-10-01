# CSAPP Data Lab

W1 的 Data Lab 实验包完整保存在 [handout/](handout/) 中。主要练习文件是 [bits.c](handout/bits.c)；编码规则和工具说明以实验包自带的 [README](handout/README) 为准。

在仓库根目录执行：

```sh
cd labs/csapp/datalab/handout
make btest
./btest
./dlc bits.c
```

`btest` 检查结果，`dlc` 检查实验限制；修改 `bits.c` 后需要重新构建 `btest`。实验包的 Makefile 使用 `-m32`，因此重新编译需要本机的 32 位开发工具链。每日进度与遇到的问题记录在 [日记](../../../journal/) 中，不把未通过的题标成完成。
