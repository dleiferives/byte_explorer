#include <stdio.h>
#include <stdlib.h>
int hex_char_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';  // Convert '0' to 0, '1' to 1, and so on
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;  // Convert 'a' to 10, 'b' to 11, and so on
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;  // Convert 'A' to 10, 'B' to 11, and so on
    } else {
        // Invalid input character
        // You can handle this case as needed, e.g., return an error code
        return -1;  // Indicates an error
    }
}
int string_to_int(char * s)
{
	long result =0;
	char c = s[0];
	if(c == 0) return 0;
	int mult = 10;
	if(s[0] == '0' && s[1] == 'x')
	{
		mult = 16;
		s = &s[2];
	}
	for (int i =0; (s[i] != '\0') && (s[i] != ' ') && (s[i] != '\n'); i++)
	{
		result *= mult;
		result += hex_char_int(s[i]);
	}
	return result;
}
void print_hex(unsigned char c)
{
	char s = c & 0x0F;
	char f = (c & 0xF0) >> 4;
	char mod = (s > 9) ? 'A'-10 : '0';
	char mod2 = (f > 9) ? 'A'-10 : '0';

	putchar(f+mod2);
	putchar(s+mod);

	return;
}

unsigned char buffer[512];
int buf_it = 0;
unsigned char getc_store(FILE *fp)
{
	buffer[buf_it++] = getc(fp);
	return buffer[buf_it];
}	

void print_ascii(int start, int end)
{
	for(int i =start; i <end; i++)
	{
		putchar(buffer[i]);
	}
}

#include "script_manager.c"

int main()
{
	FILE *fp = fopen("test1.bfp","r");
	ByteFile bf = parse_file(fp);
	printf("\nfile name:%s\n",bf.file_name);
	printf("starting user input cli to exit press `: \n");
	while(1)
	{
		parse_input(&bf);
	}
}

/*
int main(int argc, char *argv[])
{
	FILE *fp;

	fp = fopen(argv[1],"rb");

	if(!fp)
	{
		printf("wrong file fix\n");
		return 0;
	}

	int start_addr = 0;

	if(argc == 3)
	{
		start_addr = string_to_int(argv[2]);
		for(int i =0; i < start_addr; i++)
		{
			getc_store(fp);
		}
	}	

	printf("reading 512 bytes at %i",start_addr);
	putchar(10);


	for(int i =0; i<16; i++)
	{
		for(int j =0; j<8; j++)
		{
			print_hex(getc_store(fp));
			putchar(' ');
		}
		putchar(10);
	}
	putchar(10);

	print_ascii(0x3,0x3+8);
	putchar(10);
	return 0;
}

*/
