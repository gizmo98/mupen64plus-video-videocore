#ifndef N64_H
#define N64_H

#include "Types.h"

#define MI_INTR_DP		0x20		// Bit 5: DP intr 

struct N64Regs
{
	unsigned *MI_INTR;

	unsigned *DPC_START;
	unsigned *DPC_END;
	unsigned *DPC_CURRENT;
	unsigned *DPC_STATUS;
	unsigned *DPC_CLOCK;
	unsigned *DPC_BUFBUSY;
	unsigned *DPC_PIPEBUSY;
	unsigned *DPC_TMEM;

	unsigned *VI_STATUS;
	unsigned *VI_ORIGIN;
	unsigned *VI_WIDTH;
	unsigned *VI_INTR;
	unsigned *VI_V_CURRENT_LINE;
	unsigned *VI_TIMING;
	unsigned *VI_V_SYNC;
	unsigned *VI_H_SYNC;
	unsigned *VI_LEAP;
	unsigned *VI_H_START;
	unsigned *VI_V_START;
	unsigned *VI_V_BURST;
	unsigned *VI_X_SCALE;
	unsigned *VI_Y_SCALE;
};

extern N64Regs REG;
extern u8 *DMEM;
extern u8 *IMEM;
extern u8 *RDRAM;
extern u64 TMEM[512];
extern u32 RDRAMSize;

#endif

