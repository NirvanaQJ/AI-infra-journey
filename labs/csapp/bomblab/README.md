# CSAPP Bomb Lab

W1–W2 的 Bomb Lab 文件完整保存在 [handout/](handout/) 中；其中 [bomb](handout/bomb) 是要调试的程序，[bomb.c](handout/bomb.c) 是实验包提供的部分源码，不能只靠它单独重新编译整个程序。

在仓库根目录执行：

```sh
cd labs/csapp/bomblab/handout
gdb ./bomb
```

反汇编可使用 `objdump -d --disassemble=phase_1 ./bomb`。已有的学习记录见 [9 月 26 日日记](../../../journal/2026-09-26.md)；后续关卡的推导继续记入对应日期的日记。
