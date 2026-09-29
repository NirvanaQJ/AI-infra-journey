// September 25 reference lab. Assumes 64-byte cache lines for this machine.
// This verifies layout; it does not measure concurrent execution performance.
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct A {
    char a;
    int b;
    char c;
};

struct B {
    int b;
    char a;
    char c;
};

struct C {
    char a;
    double b;
    int c;
};

// Aligning the enclosing object alone does not separate its fields.
struct SharedCounters {
    uint64_t a;
    uint64_t b;
};

// Each element starts on a cache-line boundary. sizeof includes tail padding,
// so consecutive elements in an array also start on cache-line boundaries.
struct CounterSlot {
    _Alignas(64) uint64_t value;
};

_Static_assert(_Alignof(struct CounterSlot) == 64,
               "This lab requires 64-byte alignment support");
_Static_assert(sizeof(struct CounterSlot) == 64,
               "Each counter must occupy one 64-byte slot");

static void print_address(const char *name, const void *address)
{
    uintptr_t n = (uintptr_t)address;
    printf("%s: address=%p, offset_in_line=%zu\n",
           name, address, (size_t)(n % 64));
}

int main(void)
{
    printf("char:   size=%zu align=%zu\n", sizeof(char), _Alignof(char));
    printf("int:    size=%zu align=%zu\n", sizeof(int), _Alignof(int));
    printf("double: size=%zu align=%zu\n", sizeof(double), _Alignof(double));

    printf("A: size=%zu align=%zu offsets(a,b,c)=%zu,%zu,%zu\n",
           sizeof(struct A), _Alignof(struct A),
           offsetof(struct A, a), offsetof(struct A, b), offsetof(struct A, c));
    printf("B: size=%zu align=%zu offsets(b,a,c)=%zu,%zu,%zu\n",
           sizeof(struct B), _Alignof(struct B),
           offsetof(struct B, b), offsetof(struct B, a), offsetof(struct B, c));
    printf("C: size=%zu align=%zu offsets(a,b,c)=%zu,%zu,%zu\n",
           sizeof(struct C), _Alignof(struct C),
           offsetof(struct C, a), offsetof(struct C, b), offsetof(struct C, c));

    _Alignas(64) struct SharedCounters shared = {0};
    struct CounterSlot isolated[2] = {0};

    printf("SharedCounters: size=%zu type_align=%zu (object aligned to 64)\n",
           sizeof shared, _Alignof(struct SharedCounters));
    print_address("shared.a", &shared.a);
    print_address("shared.b", &shared.b);
    printf("CounterSlot: size=%zu align=%zu\n",
           sizeof(struct CounterSlot), _Alignof(struct CounterSlot));
    print_address("isolated[0].value", &isolated[0].value);
    print_address("isolated[1].value", &isolated[1].value);

    assert((uintptr_t)&shared.a / 64 == (uintptr_t)&shared.b / 64);
    assert((uintptr_t)&isolated[0].value % 64 == 0);
    assert((uintptr_t)&isolated[1].value % 64 == 0);
    assert((uintptr_t)&isolated[0].value / 64 !=
           (uintptr_t)&isolated[1].value / 64);
    puts("Layout checks passed. Predict A/B/C before running this lab.");
    return 0;
}
