#include <stdio.h>

/* 题 1：指针算术与步长（直接观察，不用写） */
void drill1(void) {
    int a[5] = {1, 2, 3, 4, 5};
    printf("a            = %p\n", (void*)a);
    printf("a + 1        = %p   差 %ld 字节\n",
           (void*)(a + 1), (char*)(a + 1) - (char*)a);
    printf("(char*)a + 1 = %p   差 %ld 字节\n",
           (void*)((char*)a + 1), (char*)((char*)a + 1) - (char*)a);
    printf("*(a+2)=%d   a[2]=%d   *a+2=%d\n", *(a+2), a[2], *a+2);
}

/* 题 2：手写 strlen —— 只用指针，不许用下标 [] 和 sizeof 数组 */
size_t my_strlen(const char *s) {
    const char *p = s;
    while (*p != '\0') p++;
    return p - s;          /* 指针相减 = 元素个数 */
}

/* 题 3：字符串反转（双指针，原地修改）—— TODO：自己写 */
void reverse(char *s) {
    char *l = s, *r = s;
    /* 先把 r 移到最后一个字符（不是 '\0'），再两头交换向中间靠 */
    /* 提示：先 while (*r) r++; 然后 r--; */
}

/* 题 4：函数指针 —— 这个模式未来在 NCCL 里到处都是 */
int square(int x) { return x * x; }
int negate(int x) { return -x; }
void apply(int *arr, int n, int (*f)(int)) {
    for (int i = 0; i < n; i++) arr[i] = f(arr[i]);
}

/* 题 5：用 unsigned char* 遍历 int 的每个字节 —— TODO：自己写
   目标：不用 gdb，用 C 代码重做周二的字节序实验 */
void print_bytes(void *ptr, size_t size) {
    unsigned char *p = (unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) printf("%02x ", p[i]);
    printf("\n");
}

int main(void) {
    drill1();

    char s[] = "hello";
    printf("strlen(\"hello\") = %zu\n", my_strlen(s));
    reverse(s);
    printf("reversed = %s\n", s);

    int arr[] = {1, 2, 3, 4, 5};
    apply(arr, 5, square);                 /* 传 square */
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n");
    apply(arr, 5, negate);                 /* 同一个函数，换个行为 */
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\n");

    int x = 0x12345678;
    print_bytes(&x, sizeof(x));            /* 观察输出是不是 78 56 34 12 */
    return 0;
}
