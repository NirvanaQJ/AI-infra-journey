// CSAPP array/structure addressing and bounds-checking exercise.
// Observe get_struct_b_unchecked in objdump, but call it only with valid i.
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

struct A {
    char a;
    int b;
    char c;
};

int get_array_item(const int *array, size_t i)
{
    return array[i];
}

int get_struct_b_unchecked(const struct A *array, size_t i)
{
    return array[i].b;
}

// Preconditions: array points to count elements; out is writable.
bool get_struct_b(const struct A *array, size_t count, size_t i, int *out)
{
    if (i >= count) {
        return false;
    }
    *out = get_struct_b_unchecked(array, i);
    return true;
}

int main(void)
{
    const struct A array[2] = {
        {.a = 'a', .b = 11, .c = 'x'},
        {.a = 'b', .b = 22, .c = 'y'},
    };
    int value = 0;

    printf("A: size=%zu align=%zu offsets(a,b,c)=%zu,%zu,%zu\n",
           sizeof(struct A), _Alignof(struct A),
           offsetof(struct A, a), offsetof(struct A, b),
           offsetof(struct A, c));

    assert(get_struct_b(array, 2, 1, &value) && value == 22);
    assert(!get_struct_b(array, 2, 2, &value));
    puts("Valid index 1 returned 22; invalid index 2 was rejected.");
    return 0;
}
