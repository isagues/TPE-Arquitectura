#include <stdint.h>
#include <usrlib.h>

#define DEFAULT_FONT 0xFFFFFF
#define DEFAULT_BACKGROUND 0X000000

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void print(char* string){
    printf(string, DEFAULT_FONT, DEFAULT_BACKGROUND);
}

void printf(char* string, unsigned int fontColor, unsigned int backgroundcolor){
    sysWrite(string,fontColor,backgroundcolor);
}

void putchar(char c){
    putcharf(c,DEFAULT_FONT,DEFAULT_BACKGROUND);
}

void putcharf(char c, unsigned int fontColor, unsigned int backgroundcolor){
    char aux[2] = {0};
    aux[0] = c;
    printf(aux,fontColor,backgroundcolor);
}

void println(char* string){
    print(string);
    putchar('\n');
}

void printint(uint64_t value){
	char buffer[40];
	uintToBase(value,buffer,10);
	print(buffer);
}

void clearScreen(){
    for (int i = 0; i < getScreenWidth() * getScreenHeight(); i++)
        putchar(' ');
        
}

int getScreenWidth(){
    return horizontalPixelCount() / CHAR_WIDTH;
}

int getScreenHeight(){
    return verticalPixelCount() / CHAR_HEIGHT;
}

int strcmp(char * s1, char * s2){
	while(*s1 != 0 && *s2 != 0 && *s1 == *s2){
		s1++;
		s2++;
	}

	return *s1 == 0 && *s2 == 0;
}

int strlen(char * s){
	int rta = 0;

	while(*s)
		rta++;

	return rta;
}

int strtok(char * s, char delim, char * array[], int arraySize){
	int arrayIndex = 0;
	if(*s != delim && *s != '\0')
		array[arrayIndex++] = s;
	while( *s != '\0' ){
		if(*s == delim){
			*s = 0;
			if( *(s+1) != delim &&  (*(s+1) != '\0')){
				if(arrayIndex >= arraySize)
					return arrayIndex;
				array[arrayIndex++] = s + 1;
			}
		}
		s++;
	}
	return arrayIndex;
} 

