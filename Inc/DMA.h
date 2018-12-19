#ifndef __DMA_H__
#define __DMA_H__


typedef volatile uint32_t IoRegister;

typedef struct dmaStreamRegs dmaStreamRegs;
struct dmaStreamRegs{
	IoRegister CR;
	IoRegister NDTR;
	IoRegister PAR;
	IoRegister M0AR;
	IoRegister M1AR;
	IoRegister FCR;
};


typedef struct dmaRegs dmaRegs;
struct dmaRegs{
	IoRegister LISR;
	IoRegister HISR;
	IoRegister LIFCR;
	IoRegister HIFCR;
	dmaStreamRegs S[8];
};

#define dma1		((dmaRegs *)0x40026000)
#define dma2		((dmaRegs *)0x40026400)

// Interrupt register
#define DMA_TCIF 	(1 << 5)		// Transfer complete
#define DMA_HTIF 	(1 << 4)		// Half transfer
#define DMA_TEIF 	(1 << 3)		// Transfer error
#define DMA_DMEIF 	(1 << 2)		// DMA error
#define DMA_FEIF 	(1 << 0)		// FIFO error


// Configuration register
#define DMA_EN 	    (1 << 0)		// Enable Stream
#define DMA_DIS 	(0 << 0)		// Disable Stream

#define DMA_DMEIE	(1 << 1)		// Enable Direct mode error interrupt
#define DMA_DMEID	(0 << 1)		// Disable Direct mode error interrupt

#define DMA_TEIE    (1 << 2)		// Enable Transfer error interrupt
#define DMA_TEID    (0 << 2)		// Disable Transfer error interrupt

#define DMA_HTIE    (1 << 3)        // Enable Half transfer interrupt
#define DMA_HTID    (0 << 3)        // Disable Half transfer interrupt

#define DMA_TCIE    (1 << 4)		// Enable Complete interrupt
#define DMA_TCID    (1 << 4)		// Disable Complete interrupt

#define DMA_PFCTRL  (1 << 5)		// Set Peripheral to flow controller

#define DMA_PFCTRLD  (0 << 5)		// Set DMA to flow controller

#define DMA_DIR_PtM (00 << 6)		// Set data transfer direction to Peripheral to Memory
#define DMA_DIR_MtP (1 << 6)		// Set data transfer direction to Memory to Peripheral
#define DMA_DIR_MtM (2 << 6)		// Set data transfer direction to Memory to Memory
#define DMA_DIR_REV (3 << 6)		// Reserved

#define DMA_CIRC	(1 << 8)		// Enable Circular mode
#define DMA_CIRCD	(0 << 8)		// Disable Circular mode

#define DMA_PINC	(1 << 9)		// Enable Peripheral pointer increment after each data transfer
#define DMA_PINCD	(0 << 9)		// Disable Peripheral pointer increment after each data transfer

#define DMA_MINC	(1 << 10)		// Enable Memory address pointer increment after each data transfer
#define DMA_MINCD	(0 << 10)		// Disable Memory address pointer increment after each data transfer

#define DMA_PSIZE8   (00 << 11)		// Set peripheral data size to 8-bit
#define DMA_PSIZE16  (1 << 11)		// Set peripheral data size to 16-bit
#define DMA_PSIZE32  (2 << 11)		// Set peripheral data size to 32-bit
#define DMA_PSIZER   (3 << 11)		// Reserved

#define DMA_MSIZE8   (00 << 13)		// Set memory data size to 8-bit
#define DMA_MSIZE16  (1 << 13)		// Set memory data size to 16-bit
#define DMA_MSIZE32  (2 << 13)		// Set memory data size to 32-bit
#define DMA_MSIZER   (3 << 13)		// Reserved

#define DMA_PINCOS   (0 << 15)		// Peripheral increment offset size is PSIZE
#define DMA_PINCOSF  (1 << 15)		// Peripheral increment offset size is 4 bytes (fixed)

#define DMA_PLL		 (00 << 16)     // Set the priority level to low
#define DMA_PLM		 (1 << 16)     // Set the priority level to medium
#define DMA_PLH		 (2 << 16)     // Set the priority level to high
#define DMA_PLVH	 (3 << 16)     // Set the priority level to very high

#define DMA_DBME	(1 << 18)		// Enable Double buffer mode
#define DMA_DBMD	(1 << 18)		// Disable Double buffer mode

#define DMA_CT0		(0 << 19)		// Current target Memory 0
#define DMA_CT1		(1 << 19)		// Current target Memory 1

#define DMA_PBURSTS  (00 << 21)     // Single transfer
#define DMA_PBURST4  (1 << 21)     // Incremental burst of 4 beats
#define DMA_PBURST8  (2 << 21)     // Incremental burst of 8 beats
#define DMA_PBURST16 (3 << 21)     // Incremental burst of 16 beats

#define DMA_MBURSTS  (00 << 23)		// Single transfer
#define DMA_MBURST4  (1 << 23)     // Incremental burst of 4 beats
#define DMA_MBURST8  (2 << 23)     // Incremental burst of 8 beats
#define DMA_MBURST16 (3 << 23)     // Incremental burst of 16 beats


#define DMA_CH0SEL 	(000 << 25)		// Channel 0 selected
#define DMA_CH1SEL 	(1 << 25)		// Channel 1 selected
#define DMA_CH2SEL 	(2 << 25)		// Channel 2 selected
#define DMA_CH3SEL 	(3 << 25)		// Channel 3 selected
#define DMA_CH4SEL 	(4 << 25)		// Channel 4 selected
#define DMA_CH5SEL 	(5 << 25)		// Channel 5 selected
#define DMA_CH6SEL 	(6 << 25)		// Channel 6 selected
#define DMA_CH7SEL 	(7 << 25)		// Channel 7 selected

#define dmaClearAllFlags(dma, chn)     dmaClearStatus(dma, chn, DMA_TCIF  |  \
																DMA_HTIF  |	 \
																DMA_TEIF  |  \
																DMA_DMEIF |	 \
																DMA_FEIF)
#endif // __DMA_H__
