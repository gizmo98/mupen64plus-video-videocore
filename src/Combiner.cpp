#include <stdint.h>
#include <stdlib.h>
#include "Combiner.h"
#include "Debug.h"
#include "GBI.h"
#include "gDP.h"

int saRGBExpanded[] = 
{
	COMBINED,			TEXEL0,				TEXEL1,				PRIMITIVE,		
	SHADE,				ENVIRONMENT,		ONE,				NOISE,
	ZERO,				ZERO,				ZERO,				ZERO,
	ZERO,				ZERO,				ZERO,				ZERO
};

int sbRGBExpanded[] = 
{
	COMBINED,			TEXEL0,				TEXEL1,				PRIMITIVE,		
	SHADE,				ENVIRONMENT,		CENTER,				K4,
	ZERO,				ZERO,				ZERO,				ZERO,
	ZERO,				ZERO,				ZERO,				ZERO
};

int mRGBExpanded[] = 
{
	COMBINED,			TEXEL0,				TEXEL1,				PRIMITIVE,		
	SHADE,				ENVIRONMENT,		SCALE,				COMBINED_ALPHA,
	TEXEL0_ALPHA,		TEXEL1_ALPHA,		PRIMITIVE_ALPHA,	SHADE_ALPHA,
	ENV_ALPHA,			LOD_FRACTION,		PRIM_LOD_FRAC,		K5,
	ZERO,				ZERO,				ZERO,				ZERO,
	ZERO,				ZERO,				ZERO,				ZERO,
	ZERO,				ZERO,				ZERO,				ZERO,
	ZERO,				ZERO,				ZERO,				ZERO
};

int aRGBExpanded[] = 
{
	COMBINED,			TEXEL0,				TEXEL1,				PRIMITIVE,		
	SHADE,				ENVIRONMENT,		ONE,				ZERO
};

int saAExpanded[] = 
{
	COMBINED,			TEXEL0_ALPHA,		TEXEL1_ALPHA,		PRIMITIVE_ALPHA,		
	SHADE_ALPHA,		ENV_ALPHA,			ONE,				ZERO
};

int sbAExpanded[] = 
{
	COMBINED,			TEXEL0_ALPHA,		TEXEL1_ALPHA,		PRIMITIVE_ALPHA,		
	SHADE_ALPHA,		ENV_ALPHA,			ONE,				ZERO
};

int mAExpanded[] = 
{
	LOD_FRACTION,		TEXEL0_ALPHA,		TEXEL1_ALPHA,		PRIMITIVE_ALPHA,		
	SHADE_ALPHA,		ENV_ALPHA,			PRIM_LOD_FRAC,		ZERO,
};

int aAExpanded[] = 
{
	COMBINED,			TEXEL0_ALPHA,		TEXEL1_ALPHA,		PRIMITIVE_ALPHA,		
	SHADE_ALPHA,		ENV_ALPHA,			ONE,				ZERO
};

int CCEncodeA[] =
{
	0, 1, 2, 3, 4, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 15, 15, 6, 15
};

int CCEncodeB[] =
{
	0, 1, 2, 3, 4, 5, 6, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 15, 15, 15
};

int CCEncodeC[] =
{
	0, 1, 2, 3, 4, 5, 31, 6, 7, 8, 9, 10, 11, 12, 13, 14, 31, 31, 15, 31, 31
};

int CCEncodeD[] =
{
	0, 1, 2, 3, 4, 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 6, 15
};

uint64_t ACEncodeA[] =
{
	7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 6, 7
};

uint64_t ACEncodeB[] =
{
	7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 6, 7
};

uint64_t ACEncodeC[] =
{
	7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 2, 3, 4, 5, 7, 6, 7, 7, 7, 7, 7
};

uint64_t ACEncodeD[] =
{
	7, 7, 7, 7, 7, 7, 7, 7, 0, 1, 2, 3, 4, 5, 7, 7, 7, 7, 7, 6, 7
};

void Combiner_Init()
{
}

void Combiner_UpdateCombineColors()
{
	gDP.changed &= ~CHANGED_COMBINE_COLORS;
}

void Combiner_BeginTextureUpdate()
{
}

void Combiner_EndTextureUpdate()
{
}

uint64_t Combiner_EncodeCombineMode( uint16_t saRGB0, uint16_t sbRGB0, uint16_t mRGB0, uint16_t aRGB0,
								 uint16_t saA0,   uint16_t sbA0,   uint16_t mA0,   uint16_t aA0,
								 uint16_t saRGB1, uint16_t sbRGB1, uint16_t mRGB1, uint16_t aRGB1,
								 uint16_t saA1,   uint16_t sbA1,   uint16_t mA1,   uint16_t aA1 )
{
	return (((uint64_t)CCEncodeA[saRGB0] << 52) | ((uint64_t)CCEncodeB[sbRGB0] << 28) | ((uint64_t)CCEncodeC[mRGB0] << 47) | ((uint64_t)CCEncodeD[aRGB0] << 15) |
		    ((uint64_t)ACEncodeA[saA0] << 44) | ((uint64_t)ACEncodeB[sbA0] << 12) | ((uint64_t)ACEncodeC[mA0] << 41) | ((uint64_t)ACEncodeD[aA0] << 9) |
			((uint64_t)CCEncodeA[saRGB1] << 37) | ((uint64_t)CCEncodeB[sbRGB1] << 24) | ((uint64_t)CCEncodeC[mRGB1]      ) | ((uint64_t)CCEncodeD[aRGB1] <<  6) |
			((uint64_t)ACEncodeA[saA1] << 18) | ((uint64_t)ACEncodeB[sbA1] <<  3) | ((uint64_t)ACEncodeC[mA1] << 18) | ((uint64_t)ACEncodeD[aA1]     ));
}

