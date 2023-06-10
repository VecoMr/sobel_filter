#include <stdint.h>

uint64_t rdtsc()
{
    unsigned long long cycle_count;
    asm volatile("mrs %0, cntvct_el0" : "=r"(cycle_count));
    return cycle_count;
}
