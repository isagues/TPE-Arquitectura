#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>
#include <screenDriver.h>
#include <idtLoader.h>
#include <timerTick.h>
#include <keyboardDriver.h>


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main()
{	
	init_screen();
	putchar('\b');
	printString("a");
	printString("hola como andas");
	putchar('\n');
	setCursorPos(126,22);
	printString("hola");
	
	putchar('\b');
	putchar('\b');
	putchar('\b');
	putchar('\b');
	putchar('\b');
	putchar('\b');
	
	printString("guadaaa");
	putchar('\b');
	printString("como andas");
	putchar('\t');
	printString("tobi");
	return ((EntryPoint)sampleCodeModuleAddress)();

}
