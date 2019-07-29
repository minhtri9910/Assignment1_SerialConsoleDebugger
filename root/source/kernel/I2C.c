#include "../../include/kernel/I2C.h"

void I2C_init()
{
    /* C Register (Control Register) - enable interrupts, clear the FIFO, 
define a read or write operation and start a transfer */ 
    I2C_control_t control;
    bzero (&control, 4);
    


/* the Read field specifies the type of transfer */


/* the CLEAR field is used to clear the FIFO. Writing to this field is 
one-shot operation which will always read back as zero. the CLEAR bit 
can set at the same time as the start transfer bit, and will result 
in the FIFO being cleared just prior to the start of transfer. Note that 
clearing the FIFO during a transfer will result in the transfer being aborted */

/* The ST field starts a new BSC transfer. This has one shot action, 
and so the bit will always read back as 0. */

/* The INTD field enables interrupts at the end of a transfer the 
DONE condition. The interrupt remains active until the DONE condition 
is cleared by writing a 1 to the I2CS.DONE field. Writing a 0 to 
the INTD field disables interrupts on DONE. */

/* The INTT field enables  interrupts whenever the FIFO is or more 
empty and needs writing (i.e during a write transfer) - The TXW 
condition. The interrupt remains active until the TXW condition is 
cleared by writing sufficient data to the FIO to complete the 
transfer. Writing a 0 to the INTT field  disables interrupts on TXW. */

/* The INTR field enables interrupts whenever the FIFO is more full 
and needs reading (i.e during a read transfer) - the RXR condition. 
The interrupt remains active until the RXW condition is cleared by 
reading sufficient data from the RX FIFO. Writing a 0 to the INTR 
field disables interrupts on RXR. */

/*The I2CEN field enables BSC operations. If this bit is 0 then transfer 
will not be performed. All register accesses are still permitted however. */
}