# CSAPP 第 7 章：静态链接、符号解析与重定位

## 从源码到可执行文件

编译器分别将源文件做成可重定位目标文件 `.o`；链接器将这些文件以及需要的库成员组合，生成可执行文件。链接器的两个核心工作是：**符号解析**，确定每个外部引用对应哪一个定义；**重定位**，合并节并修正代码或数据中的地址引用。[CSAPP 第 7 章预览](https://csapp.cs.cmu.edu/2e/ch7-preview.pdf)

**通俗理解：**每份 `.o` 像写着“要用 `bump`，但地址待填”的零件清单。符号解析找到提供 `bump` 的零件；重定位把最终连接位置写进调用指令。

## `.o` 中要看什么

| 内容 | 作用 | 常用命令 |
| --- | --- | --- |
| ELF 头 | 文件是 `REL`、`EXEC` 等哪种类型 | `readelf -h` |
| `.text`、`.data`、`.bss` | 代码、已初始化数据、零初始化数据 | `readelf -S` |
| `.symtab` | 定义与未定义的符号；`UND` 表示本文件尚无定义 | `readelf -s` |
| `.rela.text` 等 | 需修正的位置、重定位类型、目标符号和加数 | `readelf -r` |
| 反汇编 | 把重定位记录对应到具体指令 | `objdump -dr` |

`gcc -c` 只完成目标文件生成；不做最后的链接。文件作用域的 C `static` 控制名字只在当前翻译单元可见，与“静态链接”不是同一个概念。这里的静态链接指构建时处理 `.o` 和按需取用 `.a` 的成员；程序也可能仍依赖动态库。[GNU ld 文档](https://sourceware.org/binutils/docs/ld.html)

## 符号解析规则

以本仓库 [链接练习](../../exercises/c/linking-oct02/README.md) 为例，`main.c` 中 `extern int value;` 是声明，`helper.c` 中 `int value = 3;` 是定义。`main.o` 的 `value` 为 `UND`，`helper.o` 的 `value` 则是已定义的 `OBJECT`；链接器把引用匹配到这个定义。

找不到定义会产生 `undefined reference`；存在冲突的强定义会产生 `multiple definition`。教材中的强、弱符号例子要结合工具链版本理解：GCC 10 起默认 `-fno-common`，多个翻译单元各写一个 `int x;` 通常报重复定义，而不是自动按旧式 common 符号合并。可靠写法是在头文件放 `extern int x;`，只在一个 `.c` 中定义 `x`。[GCC 10 移植说明](https://gcc.gnu.org/gcc-10/porting_to.html)

## 重定位规则与本次实例

符号解析回答“引用的是哪个定义”，重定位回答“这处引用要写入什么值”。在 x86-64 的 PC 相对寻址中，链接后指令中的位移可理解为：

```text
目标符号地址 - 下一条指令地址
```

本次 `main.o` 的 `.rela.text` 对 `value` 有 `R_X86_64_PC32` 记录，链接前读取指令为 `mov 0x0(%rip),%eax`。最终 `value=0x403000`、下一条指令地址 `0x40101c`，所以位移是 `0x1fe4`。对 `bump` 的 `R_X86_64_PLT32` 记录则在本次静态链接中成为直接调用；重定位类型带 `PLT` 不意味着最终一定跳经 PLT。完整原始输出和 `ld` 命令见 [练习记录](../../exercises/c/linking-oct02/README.md)。

## 为什么手动 `ld` 要有 `_start`

日常用 `gcc` 完成最终链接时，驱动程序会安排运行时启动文件和所需库。直接用 `ld` 链接本练习的两个 C 目标文件时，需要自己提供入口。练习中的 `start.S` 定义 `_start`、调用 `main`，再通过 Linux x86-64 系统调用退出。它只适合这个不使用标准库的最小例子，不能代替一般 C 程序的完整启动流程。
