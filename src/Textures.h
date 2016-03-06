#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>

struct gDPTile;

inline uint8_t TextureCache_SizeToBPP(uint8_t size) {
    switch (size) {
    case 0:     return 4;
    case 1:     return 8;
    case 2:     return 16;
    default:    return 32;
    }
}

int32_t TextureCache_GetTexel(gDPTile *tile, int32_t s, int32_t t);
int32_t TextureCache_GetTexelFromBGImage(uint8_t *swapped, int32_t s, int32_t t);

#endif

