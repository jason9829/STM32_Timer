/*
 *	DMA.c
 */

#include "DMA.h"
#include "RCC.h"

int dmaGetStatus(dmaRegs *dma, int channel, int flags){

	int channelShifts;
	int tempFlags;

	switch(channel){
	case 0 : case 4 : channelShifts = 0;
					  break;
	case 1 : case 5 : channelShifts = 6;
					  break;
	case 2 : case 6 : channelShifts = 16;
					  break;
	case 3 : case 7 : channelShifts = 22;
					  break;
	}

	tempFlags = flags << channelShifts;

	/* eg
	 * 		1 0 0 1		Interrupt status register
	 * 	&	0 0 0 1		tempFlags	(depend on Flag but only one bit is '1')
	 * 	------------
	 * 	    0 0 0 1
	 *
	 */

	if((dma->LISR & tempFlags)){
		return 1;
	}
	else if((dma->HISR & tempFlags)){
		return 1;
	}
	else{
		return 0;
	}

}


void dmaClearStatus(dmaRegs *dma, int channel, int flags){
	int channelShifts;
	int tempFlags;

	switch(channel){
	case 0 : case 4 : channelShifts = 0;
					  break;
	case 1 : case 5 : channelShifts = 6;
					  break;
	case 2 : case 6 : channelShifts = 16;
					  break;
	case 3 : case 7 : channelShifts = 22;
					  break;
	}

	tempFlags = ~((flags) << channelShifts);

	/* flags =  00000000100
	 *
	 * ~flags = 11111111011
	 * reg    = 01011101100		&
	 * result = 01011101011
	 *
	 *  eg (want to clear bit 3,4)
	 *  	1 1 0 1 	Interrupt status register
	 *  &	0 0 1 1 	tempFlags (Flags = 1 1 0 0)
     *  -----------
     *      0 0 0 1
     **/

	if(channel <= 3){
		dma->LISR = (dma->LISR & tempFlags);
	}
	else{
		dma->HISR = (dma->HISR & tempFlags);
	}

}

void dmaConfigureStream(dmaRegs *dma, int channel, int configuration){
	dma->S[channel]-> CR |= configuration;
}
