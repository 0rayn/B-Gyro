# pragma once

# include "klibc/types.h"
# include "arch/i386/serialCommunication/serialIO.h"

typedef uint8_t (*putCharFnc)(char);
typedef struct buff
{
	char		*buff;
	uint32_t	index;
}_buff;

int     print(putCharFnc fnc, char *fmtString, ...);
void    setSprintBuff(char *buff);
uint8_t appendsprintBuff(char c);

#define SERIAL_PRINT(FMT_STRING, ...) print(serialPutCharacter, FMT_STRING, __VA_ARGS__)

// Prints a string to the VGA doesn't update the state of the yonaData.
#define SERIAL_INFO(FMT_STRING, ...)    print(serialPutCharacter, "\033[34mINFO\033[39m  [%s] " FMT_STRING, __func__, __VA_ARGS__)
#define SERIAL_SUCC(FMT_STRING, ...)    print(serialPutCharacter, "\033[92mSUCC\033[39m  [%s] " FMT_STRING, __func__, __VA_ARGS__)
#define SERIAL_ERR(FMT_STRING, ...)     print(serialPutCharacter, "\033[31mERR\033[39m   [%s] " FMT_STRING, __func__, __VA_ARGS__)
#define SERIAL_DEBUG(FMT_STRING, ...)   print(serialPutCharacter, "\033[93mDEBUG\033[39m [%s] " FMT_STRING, __func__, __VA_ARGS__)