/////////////////////////////////////////////////////////////////////////////////////////////////////////
//					Printf via SerialWireOutput using ARM Cortex M3/M4 ITM functionality
//					Link DEMCR: https://developer.arm.com/documentation/ddi0439/b/Debug/About-debug/Debug-register-summary
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//How to use: add this code snippet from line no 10 to line no 31 to syscalls.c file before functions are written 
//& modify _write API in syscalls.c as mentioned below

//Debug Exception and Monitor Control Register base address
#define DEMCR        			*((volatile uint32_t*) 0xE000EDFCU )

/* ITM register addresses */
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )

void ITM_SendChar(uint8_t ch)
{

	//Enable TRCENA
	DEMCR |= ( 1 << 24);

	//enable stimulus port 0
	ITM_TRACE_EN |= ( 1 << 0);

	// read FIFO status in bit [0]:
	while(!(ITM_STIMULUS_PORT0 & 1));

	//Write to ITM stimulus port0
	ITM_STIMULUS_PORT0 = ch;
}


//Modify _write function API as below in 
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		//__io_putchar(*ptr++); //comment it
		ITM_SendChar(*ptr++); // add it
	}
	return len;
}