#ifndef __KERNEL__
#define __KERNEL__

#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"
#include "../../include/common/stdio.h"
#include "../../include/common/mystdlib.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags);

#endif