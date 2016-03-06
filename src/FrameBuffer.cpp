#include <stdlib.h>
#include "FrameBuffer.h"
#include "RSP.h"
#include "RDP.h"
#include "Combiner.h"
#include "Types.h"

FrameBufferInfo frameBuffer;

void FrameBuffer_Init()
{
}

void FrameBuffer_RemoveBottom()
{
}

void FrameBuffer_Remove( FrameBuffer *buffer )
{
}

void FrameBuffer_RemoveBuffer( u32 address )
{
}

FrameBuffer *FrameBuffer_AddTop()
{
    return NULL;
}

void FrameBuffer_MoveToTop( FrameBuffer *newtop )
{
}

void FrameBuffer_Destroy()
{
}

void FrameBuffer_SaveBuffer( u32 address, u16 size, u16 width, u16 height )
{
	gSP.changed |= CHANGED_TEXTURE;
}

void FrameBuffer_RenderBuffer( u32 address )
{
}

void FrameBuffer_RestoreBuffer( u32 address, u16 size, u16 width )
{
}

FrameBuffer *FrameBuffer_FindBuffer( u32 address )
{
	return NULL;
}

void FrameBuffer_ActivateBufferTexture( s16 t, FrameBuffer *buffer )
{
	FrameBuffer_MoveToTop( buffer );
}
