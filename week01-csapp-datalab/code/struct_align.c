#include <stdio.h>
#include <stddef.h>

/* 成员顺序「坏」的写法 */
struct A {
    char c;      /* 1 字节 */
    int  i;      /* 4 字节 */
    char c2;     /* 1 字节 */
};

/* 同样的三个成员，换个顺序 */
struct B {
    int  i;
    char c;
    char c2;
};

/* 模拟网络协议头：强制紧密排列 */
struct NetHdr {
    unsigned char  type;
    unsigned short len;
    unsigned int   seq;
} __attribute__((packed));

/* 上面那个如果不 packed，对比用 */
struct NetHdrRaw {
    unsigned char  type;
    unsigned short len;
    unsigned int   seq;
};

int main(void) {
    printf("=== struct A: char / int / char ===\n");
    printf("sizeof = %zu\n", sizeof(struct A));
    printf("  offset(c)=%zu  offset(i)=%zu  offset(c2)=%zu\n",
           offsetof(struct A, c), offsetof(struct A, i), offsetof(struct A, c2));

    printf("=== struct B: int / char / char ===\n");
    printf("sizeof = %zu\n", sizeof(struct B));
    printf("  offset(i)=%zu  offset(c)=%zu  offset(c2)=%zu\n",
           offsetof(struct B, i), offsetof(struct B, c), offsetof(struct B, c2));

    printf("=== 网络协议头 ===\n");
    printf("packed   sizeof = %zu\n", sizeof(struct NetHdr));
    printf("unpacked sizeof = %zu\n", sizeof(struct NetHdrRaw));

    /* 规模效应：一百万个结构体差多少内存 */
    printf("\n=== 100 万个结构体 ===\n");
    printf("A: %zu MB   B: %zu MB   差 %.1f MB\n",
           sizeof(struct A) * 1000000 / 1024 / 1024,
           sizeof(struct B) * 1000000 / 1024 / 1024,
           (sizeof(struct A) - sizeof(struct B)) * 1000000.0 / 1024 / 1024);
    return 0;
}
