#include "tui.h"
#include "script_manager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	// set up the terminal
	Terminal_t term;
	term = Terminal_t_init();
	Terminal_t_create(&term);
	Terminal_t_move_cursor(&term,0,0);
	
	ByteFile bf = ByteFile_zero();
	if(argc == 2) {
		printf("Setting your file to %s\n",argv[1]);
		int i=0;
		for(; argv[i] != 0; i++)
		{
			bf.file_name[i] = argv[1][i];
		}
		bf.file_name[i+1] =0;
	}

	printf("starting user input cli start typing");
	while(1)
	{
		Terminal_t_parse_input(&term,&bf);
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
