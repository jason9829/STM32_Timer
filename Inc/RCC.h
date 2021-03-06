#ifndef __RCC_H__
#define __RCC_H__

typedef volatile uint32_t RCCRegister;

typedef struct RCCRegs RCCRegs;
struct RCCRegs{				//  Offset	// Description
	RCCRegister cr;				//	0x00	// clock control register
	RCCRegister pllcfgr;		//	0x04	// pll configuration register
	RCCRegister cfgr;			//	0x08	// clock configuration register
	RCCRegister cir;			//	0x0c	// clock interrupt register
	RCCRegister ahb1rstr;		//	0x10	// ahb1 peripheral reset register
	RCCRegister ahb2rstr;		//	0x14	// ahb2 peripheral reset register
	RCCRegister ahb3rstr;		//	0x18	// ahb3 peripheral reset register
	RCCRegister rev0;			//	0x1c	// reversed0
	RCCRegister apb1rstr;		//	0x20	// apb1 peripheral reset register
	RCCRegister apb2rstr;		//	0x24	// apb2 peripheral reset register
	RCCRegister rev1[2];		//	0x28/ 0x2c	//	reversed1 for the two locations
	RCCRegister ahb1enr;		//	0x30	// ahb1 peripheral clock enable register
	RCCRegister ahb2enr;		//	0x34	// ahb2 peripheral clock enable register
	RCCRegister ahb3enr;		//	0x38	// ahb3 peripheral clock enable register
	RCCRegister rev2;			//	0x3c	// reversed2
	RCCRegister apb1enr;		//	0x40	// apb1 peripheral clock enable register
	RCCRegister apb2enr;		//	0x44	// apb2 peripheral clock enable register
	RCCRegister rev3[2];		//	0x48/ 0x4c	//	reversed3 for the two locations
	RCCRegister ahb1lpenr;		//	0x50	// ahb1 peripheral clock enable in low power mode register
	RCCRegister ahb2lpenr;		//  0x54	// ahb2 peripheral clock enable in low power mode register
	RCCRegister ahb3lpenr;		//  0x58	// ahb3 peripheral clock enable in low power mode register
	RCCRegister rev4;			//  0x5c	// reversed4
	RCCRegister apb1lpenr;		//  0x60	// apb1 peripheral clock enable in low power mode register
	RCCRegister apb12penr;		//  0x64	// apb2 peripheral clock enable in low power mode register
	RCCRegister rev5[2];		//	0x68/ 0x6c	//	reversed5 for the two locations
	RCCRegister bdcr;			//	0x70	// backup domain control register
	RCCRegister csr;			//	0x74	// clock control & status register
	RCCRegister rev6[2];		//	0x78/ 0x7c	//	reversed6 for the two locations
	RCCRegister sscgr;			//	0x80	// spread spectrum clock generation register
	RCCRegister plli2scfgr;		//	0x84	// plli2scfgr configuration register
};

#define rcc		((RCCRegs*) 0x40023800)

/********************* apb1enr(peripheral clock enable register) ******************/
#define ENABLE_TIMER_2_CLK_GATING()			rcc->apb1enr |= (1 << 0)
#define ENABLE_TIMER_3_CLK_GATING()			rcc->apb1enr |= (1 << 1)
#define ENABLE_TIMER_4_CLK_GATING()			rcc->apb1enr |= (1 << 2)
#define ENABLE_TIMER_5_CLK_GATING()			rcc->apb1enr |= (1 << 3)
#define ENABLE_TIMER_6_CLK_GATING()			rcc->apb1enr |= (1 << 4)
#define ENABLE_TIMER_7_CLK_GATING()			rcc->apb1enr |= (1 << 5)
#define ENABLE_TIMER_12_CLK_GATING()		rcc->apb1enr |= (1 << 6)
#define ENABLE_TIMER_13_CLK_GATING()		rcc->apb1enr |= (1 << 7)
#define ENABLE_TIMER_14_CLK_GATING()		rcc->apb1enr |= (1 << 8)


// For DMA
#define ENABLE_DMA1_CLK_GATING()			rcc->ahb1enr |= (1 << 21)
#define ENABLE_DMA2_CLK_GATING()			rcc->ahb1enr |= (1 << 22)


#define DISABLE_TIMER_2_CLK_GATING()		rcc->apb1enr &= ~(1 << 0)
#define DISABLE_TIMER_3_CLK_GATING()		rcc->apb1enr &= ~(1 << 1)
#define DISABLE_TIMER_4_CLK_GATING()		rcc->apb1enr &= ~(1 << 2)
#define DISABLE_TIMER_5_CLK_GATING()		rcc->apb1enr &= ~(1 << 3)
#define DISABLE_TIMER_6_CLK_GATING()		rcc->apb1enr &= ~(1 << 4)
#define DISABLE_TIMER_7_CLK_GATING()		rcc->apb1enr &= ~(1 << 5)
#define DISABLE_TIMER_12_CLK_GATING()		rcc->apb1enr &= ~(1 << 6)
#define DISABLE_TIMER_13_CLK_GATING()		rcc->apb1enr &= ~(1 << 7)
#define DISABLE_TIMER_14_CLK_GATING()		rcc->apb1enr &= ~(1 << 8)


// For DMA
#define DISABLE_DMA1_CLK_GATING()		rcc->ahb1enr &= ~(1 << 21)
#define DISABLE_DMA2_CLK_GATING()		rcc->ahb1enr &= ~(1 << 22)

/********************* apb1rstr(peripheral reset register) ************************/
#define UNRESET_TIMER_2_CLK_GATING()		rcc->apb1rstr &= ~(1 << 0)
#define UNRESET_TIMER_3_CLK_GATING()		rcc->apb1rstr &= ~(1 << 1)
#define UNRESET_TIMER_4_CLK_GATING()		rcc->apb1rstr &= ~(1 << 2)
#define UNRESET_TIMER_5_CLK_GATING()		rcc->apb1rstr &= ~(1 << 3)
#define UNRESET_TIMER_6_CLK_GATING()		rcc->apb1rstr &= ~(1 << 4)
#define UNRESET_TIMER_7_CLK_GATING()		rcc->apb1rstr &= ~(1 << 5)
#define UNRESET_TIMER_12_CLK_GATING()		rcc->apb1rstr &= ~(1 << 6)
#define UNRESET_TIMER_13_CLK_GATING()		rcc->apb1rstr &= ~(1 << 7)
#define UNRESET_TIMER_14_CLK_GATING()		rcc->apb1rstr &= ~(1 << 8)

// For DMA
#define UNRESET_DMA1_CLK_GATING()			rcc->ahb1rstr &= ~(1 << 21)
#define UNRESET_DMA2_CLK_GATING()			rcc->ahb1rstr &= ~(1 << 22)



#define RESET_TIMER_2_CLK_GATING()			rcc->apb1rstr |= (1 << 0)
#define RESET_TIMER_3_CLK_GATING()			rcc->apb1rstr |= (1 << 1)
#define RESET_TIMER_4_CLK_GATING()			rcc->apb1rstr |= (1 << 2)
#define RESET_TIMER_5_CLK_GATING()			rcc->apb1rstr |= (1 << 3)
#define RESET_TIMER_6_CLK_GATING()			rcc->apb1rstr |= (1 << 4)
#define RESET_TIMER_7_CLK_GATING()			rcc->apb1rstr |= (1 << 5)
#define RESET_TIMER_12_CLK_GATING()			rcc->apb1rstr |= (1 << 6)
#define RESET_TIMER_13_CLK_GATING()			rcc->apb1rstr |= (1 << 7)
#define RESET_TIMER_14_CLK_GATING()			rcc->apb1rstr |= (1 << 8)

// For DMA
#define RESET_DMA1_CLK_GATING()			    rcc->ahb1rstr |= (1 << 21)
#define RESET_DMA2_CLK_GATING()			    rcc->ahb1rstr |= (1 << 22)

#endif // __RCC_H__
