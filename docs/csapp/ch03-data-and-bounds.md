# CSAPP 第 3 章：数组、结构体与越界访问

## 章节位置与学习主线

CSAPP 第三版的 3.8 讲数组，3.9 讲结构体、联合体与对齐；越界访问和缓冲区溢出在 3.10.3。学习计划把这些内容合为一项。主线是：**对象在内存中的布局 → 汇编如何算地址 → 地址越出对象边界的后果**。[CSAPP 第三版目录](https://csapp.cs.cmu.edu/3e/pieces/preface3e.pdf)

## 数组下标与结构体成员

数组元素连续存放。对元素类型 `T`，`array[i]` 的地址是 `base + i × sizeof(T)`；例如当前 Linux x86-64 环境的 `int` 为 4 字节，`int_array[i]` 可由 `(%rdi,%rsi,4)` 寻址，其中 `%rdi` 是基址、`%rsi` 是下标。

结构体成员位置由 `offsetof` 测量，整体步长由包含填充的 `sizeof` 决定。本仓库的 `struct A { char a; int b; char c; }` 在当前环境中有 `sizeof(struct A)=12`、`offsetof(b)=4`。因此：

```text
array[i].b 的地址 = array 起始地址 + i × 12 + 4
```

编译 [数组与边界练习](../../exercises/c/oct01_array_struct_bounds.c) 的 `get_struct_b_unchecked` 可见一种实际实现：

```asm
lea  (%rsi,%rsi,2),%rax     # 3 × i
mov  0x4(%rdi,%rax,4),%eax # base + (3 × i) × 4 + 4
```

不同编译器或优化设置可以采用不同指令；应检查它计算的有效地址，而不是只认一种指令排列。

## 边界和缓冲区溢出

对 `struct A array[2]`，有效下标只有 0 和 1。`array[2].b` 的地址虽然可以算出，但访问该成员已超出对象边界，是未定义行为。读越界与写越界都不合法；写越界可能破坏邻近数据、使程序崩溃，具体结果取决于实际布局。[OWASP：Buffer Overflow](https://community.owasp.org/vulnerabilities/Buffer_Overflow)

对 `char name[8]`，若要存入 8 个普通字符形成 C 字符串，还需第 9 个字节写结尾 `\0`，因此容量不足。可靠做法是先验证长度和容量；例如要复制 `n` 个字节并补 `\0`，要求 `capacity > 0 && n < capacity`，同时保证来源有 `n` 个可读字节。

练习中的 `get_struct_b_unchecked` 用来观察原始寻址，只能用有效下标调用；`get_struct_b` 接收真实元素个数并在访问前检查 `i < count`。开发时可用 GCC 的 `-fsanitize=address` 帮助发现实际执行到的越界访问；它不能代替边界设计。[GCC：Instrumentation Options](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)

具体编译结果、Bomb Lab `phase_5` 与秘密关的推导和验证记录见 [10 月 1 日日记](../../journal/2026-10-01.md)。
