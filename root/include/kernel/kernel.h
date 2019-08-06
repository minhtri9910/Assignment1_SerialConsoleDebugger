#ifndef __KERNEL__
#define __KERNEL__

#include <stddef.h>
#include <stdint.h>
#include "../../include/kernel/uart.h"
#include "../../include/kernel/master.h"
#include "../../include/kernel/slave.h"
#include "../../include/kernel/gpio.h"
#include "../../include/common/stdio.h"
#include "../../include/common/mystdlib.h"
#include "../../include/common/mytime.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags);

#endif