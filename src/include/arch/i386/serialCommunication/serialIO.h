# pragma once
# include "klibc/types.h"

#define COM1 0x3F8

int	initSerialCOM1();
int	isTransmitEmpty();

uint8_t serialPutCharacter(char c);