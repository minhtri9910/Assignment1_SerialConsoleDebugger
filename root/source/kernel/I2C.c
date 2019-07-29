#include "../../include/kernel/I2C.h"


void I2C_init()
{
    /* C Register (Control Register) - enable interrupts, clear the FIFO, 
    define a read or write operation and start a transfer */ 
    // Set all the C_Register to 0
    I2C_control_t control;
    bzero (&control, 4);
    mmio_write(BSC0_C, control.as_int); 

    /*The I2CEN field enables BSC operations. If this bit is 0 then transfer 
    will not be performed. All register accesses are still permitted however. */
    control.I2CEN_I2C_enable = 1;

    /* the Read field specifies the type of transfer */
    // control.READ_Read_Transfer = 1;

    /* the CLEAR field is used to clear the FIFO. Writing to this field is 
    one-shot operation which will always read back as zero. the CLEAR bit 
    can set at the same time as the start transfer bit, and will result 
    in the FIFO being cleared just prior to the start of transfer. Note that 
    clearing the FIFO during a transfer will result in the transfer being aborted */
    // control.CLEAR_FIFO_Clear = 2;

    /* The ST field starts a new BSC transfer. This has one shot action, 
    and so the bit will always read back as 0. */
    // control.ST_Start_Transfer = 1;

    /* The INTD field enables interrupts at the end of a transfer the 
    DONE condition. The interrupt remains active until the DONE condition 
    is cleared by writing a 1 to the I2CS.DONE field. Writing a 0 to 
    the INTD field disables interrupts on DONE. */
    // control.INTD_interrupt_on_DONE = 1;

    /* The INTT field enables  interrupts whenever the FIFO is or more 
    empty and needs writing (i.e during a write transfer) - The TXW 
    condition. The interrupt remains active until the TXW condition is 
    cleared by writing sufficient data to the FIO to complete the 
    transfer. Writing a 0 to the INTT field  disables interrupts on TXW. */
    // control.INTT_interrupt_on_TX = 1;

    /* The INTR field enables interrupts whenever the FIFO is more full 
    and needs reading (i.e during a read transfer) - the RXR condition. 
    The interrupt remains active until the RXW condition is cleared by 
    reading sufficient data from the RX FIFO. Writing a 0 to the INTR 
    field disables interrupts on RXR. */
    // control.INTR_interrupt_on_RX = 1;

    
}

I2C_status_t read_status(void) {
        I2C_status_t status;
        status.as_int = mmio_read(BSC0_S);
        return status;
}
