while(1)
	{
		//3.SET 9th bit of the output data register to make I/O pin-12 as HIGH
		*pPortDOutReg |= ( 1 << 9);

		//introduce small human observable delay
		//This loop executes for 10K times
		for(uint32_t i=0 ; i < 300000 ; i++ );

		//Tun OFF the LED
		*pPortDOutReg &= ~( 1 << 9);

		for(uint32_t i=0 ; i < 300000 ; i++ );
	}
