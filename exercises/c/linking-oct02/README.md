# 10 月 2 日：从 `.c` 到手动链接的可执行文件

本练习对应 CSAPP 第 7 章的静态链接、符号解析与重定位。三个源码文件分别是 [`main.c`](main.c)、[`helper.c`](helper.c) 和 [`start.S`](start.S)。`main.c` 引用 `value`、`bump`，`helper.c` 提供定义；`start.S` 提供手动使用 `ld` 所需的入口 `_start`。

## 环境与构建命令

实测环境：Linux x86-64；GCC 15.2.0；GNU Binutils 2.46。以下命令均从仓库根目录运行，生成文件放在被 Git 忽略的 `build/` 中。

```sh
mkdir -p build/linking-oct02
gcc -O0 -fno-pie -fno-stack-protector -c exercises/c/linking-oct02/main.c -o build/linking-oct02/main.o
gcc -O0 -fno-pie -fno-stack-protector -c exercises/c/linking-oct02/helper.c -o build/linking-oct02/helper.o
gcc -c exercises/c/linking-oct02/start.S -o build/linking-oct02/start.o
ld -o build/linking-oct02/manual build/linking-oct02/start.o build/linking-oct02/main.o build/linking-oct02/helper.o
./build/linking-oct02/manual
echo $?
```

`gcc -c` 只生成可重定位目标文件，没有执行最终链接。`ld` 直接链接时不会自动加入 C 运行时启动代码，因此本例让 `_start` 调用 `main`，再通过 Linux x86-64 的 `exit` 系统调用返回结果；源码未调用标准库函数。

## 观察命令与原始输出

| 阶段 | 命令 | 保存的输出 |
| --- | --- | --- |
| `.o` 的类型 | `readelf -h build/linking-oct02/main.o` | [`01-elf-header.txt`](01-elf-header.txt) |
| `.o` 的节 | `readelf -S build/linking-oct02/main.o` | [`02-sections.txt`](02-sections.txt) |
| 引用方符号表 | `readelf -s build/linking-oct02/main.o` | [`03-main-symbols.txt`](03-main-symbols.txt) |
| 定义方符号表 | `readelf -s build/linking-oct02/helper.o` | [`04-helper-symbols.txt`](04-helper-symbols.txt) |
| 重定位表 | `readelf -r build/linking-oct02/main.o` | [`05-relocations.txt`](05-relocations.txt) |
| 链接前反汇编 | `objdump -dr build/linking-oct02/main.o` | [`06-before-link.txt`](06-before-link.txt) |
| 链接后符号表 | `readelf -s build/linking-oct02/manual` | [`07-final-symbols.txt`](07-final-symbols.txt) |
| 链接后反汇编 | `objdump -d build/linking-oct02/manual` | [`08-after-link.txt`](08-after-link.txt) |
| 可执行文件类型与入口 | `readelf -h build/linking-oct02/manual` | [`09-final-header.txt`](09-final-header.txt) |
| 可执行文件剩余重定位 | `readelf -r build/linking-oct02/manual` | [`10-final-relocations.txt`](10-final-relocations.txt) |
| 运行结果 | `./build/linking-oct02/manual; echo $?` | [`11-run.txt`](11-run.txt) |

## 一个符号解析实例

`main.o` 的 `value` 和 `bump` 均为 `UND`，表示在这个文件中被引用但未定义。`helper.o` 的 `value` 是已定义的 `OBJECT`，`bump` 是已定义的 `FUNC`。链接器把两个 `UND` 分别匹配到 `helper.o` 的定义。最终符号表中，`value` 位于 `0x403000`，`bump` 位于 `0x401025`。这些具体地址只属于本次构建。

## 一个重定位实例

`main.o` 的 `.rela.text` 中有 `value` 的 `R_X86_64_PC32` 记录，偏移为 `0x0a`。链接前，读取变量的指令显示为 `mov 0x0(%rip),%eax`，位移尚未确定。链接后，`value` 位于 `0x403000`，该指令下一条的地址是 `0x40101c`，因此位移为 `0x403000 - 0x40101c = 0x1fe4`；最终反汇编显示 `mov 0x1fe4(%rip),%eax # 403000 <value>`。

函数调用也一样：`bump` 的 `R_X86_64_PLT32` 记录位于偏移 `0x11`。本次链接将它修正成从 `0x401023` 到 `0x401025` 的相对位移 `2`，最终直接调用本地的 `bump`，没有经过 PLT 跳板。`PLT32` 这个重定位类型本身不表示最终一定会调用 PLT。

## 实际结果与范围

`main.o` 的 ELF 类型为 `REL`；`manual` 的类型为 `EXEC`，入口 `_start` 位于 `0x401000`。`readelf -r manual` 报告本例的最终文件没有剩余重定位。程序退出码为 `4`，对应 `bump(value) = 3 + 1`。

这里演示 Linux x86-64 上不依赖标准库的最小程序。编译器版本、优化选项或目标平台变化时，具体指令与地址可能变化；判断时应以符号、重定位记录及实际反汇编的对应关系为准。
