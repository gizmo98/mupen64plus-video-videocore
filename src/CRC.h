#ifndef CRC_H
#define CRC_H

#include <stdio.h>

void CRC_BuildTable();

uint32_t CRC_Calculate( uint32_t crc, void *buffer, uint32_t count );
uint32_t CRC_CalculatePalette( uint32_t crc, void *buffer, uint32_t count );

#endif
