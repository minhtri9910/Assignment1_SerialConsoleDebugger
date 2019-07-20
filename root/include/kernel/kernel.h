#ifndef __KERNEL__
#define __KERNEL__

#include <stddef.h>
#include <stdint.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags);

#endif