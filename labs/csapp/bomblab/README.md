# CSAPP Bomb Lab

W1–W2 的 Bomb Lab 文件完整保存在 [handout/](handout/) 中；其中 [bomb](handout/bomb) 是要调试的程序，[bomb.c](handout/bomb.c) 是实验包提供的部分源码，不能只靠它单独重新编译整个程序。

在仓库根目录执行：

```sh
cd labs/csapp/bomblab/handout
gdb ./bomb
```

反汇编可使用 `objdump -d --disassemble=phase_1 ./bomb`。已有的学习记录见 [9 月 26 日日记](../../../journal/2026-09-26.md)；后续关卡的推导继续记入对应日期的日记。

`phase_2` 与 `phase_3` 的推导、跳转表和运行结果见 [9 月 29 日日记](../../../journal/2026-9-29.md)，前三关输入见 [answers-through-phase3.txt](answers-through-phase3.txt)。`phase_4` 的递归、栈帧和运行结果见 [9 月 30 日日记](../../../journal/2026-09-30.md)，前四关输入见 [answers-through-phase4.txt](answers-through-phase4.txt)。在 `handout/` 中运行 `./bomb ../answers-through-phase4.txt </dev/null`；出现 `So you got that one.  Try this one.` 表示第四关通过，随后第五关缺少输入会报告 EOF。

`phase_5`、秘密关入口、必经的 `phase_6` 和二叉树路径推导见 [10 月 1 日日记](../../../journal/2026-10-01.md)。[answers-through-secret.txt](answers-through-secret.txt) 保存全部七行输入；在 `handout/` 中运行 `./bomb ../answers-through-secret.txt </dev/null`，出现 `Wow! You've defused the secret stage!` 表示秘密关通过。
