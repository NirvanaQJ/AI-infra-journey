#include <stdio.h>

int main(void) {
    int    i    = 0x12345678;   // 经典测试值，一眼识别字节序
    short  s    = -2;           // 0xFFFE
    long   l    = 1;            // 8 字节，看高 4 字节在哪
    float  f    = 1.0f;         // IEEE754: 0x3F800000
    float  f2   = -0.15625f;    // 课本 2.4 节经典例子
    double d    = 1.0;
    char   c    = 'A';          // 0x41
    char   str[] = "ABCDE";     // 字符串 + 结尾 \0
    int    arr[3] = {1, 0x100, -1};

    printf("int    i    = 0x12345678\n");
    printf("short  s    = -2\n");
    printf("long   l    = 1, size=%zu\n", sizeof(l));
    printf("float  f    = 1.0f\n");
    printf("float  f2   = -0.15625f\n");
    printf("double d    = 1.0\n");
    printf("char   c    = 'A'\n");
    printf("char   str[] = \"ABCDE\"\n");
    printf("int    arr[3] = {1, 0x100, -1}\n");
    printf("addresses: &i=%p &s=%p &f=%p\n", (void*)&i, (void*)&s, (void*)&f);
    return 0;
}
