# include "klibc/print.h"

void	kernelInit(){
	initSerialCOM1();
}

int	kmain(void){

	kernelInit();

	char *videoMemory = (char*)0xb8000;
	videoMemory[0] = '4';
	videoMemory[1] = 0x07;
	videoMemory[2] = '2';
	videoMemory[3] = 0x07;

	SERIAL_PRINT("Hello %s\r\n", "World !");
	SERIAL_DEBUG("Hello %s\r\n", "World !");
	SERIAL_ERR("Hello %s\r\n", "World !");
	SERIAL_INFO("Hello %s\r\n", "World !");
	SERIAL_SUCC("Hello %s\r\n", "World !");
	return 0;
}