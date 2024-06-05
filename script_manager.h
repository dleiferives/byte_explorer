#ifndef SCRIPT_MANAGER_H_
#define SCRIPT_MANAGER_H_
#include "tui.h"
#include <stdlib.h>
typedef struct
{
	int size;
	int num_items;
	int cursor;
	unsigned char * arr;
}U8_List;
typedef struct
{
	U8_List buffer;
	int buffer_size;
	int buffer_cursor;
	int read_cursor;
	FILE * fp;
	char file_name[256];
	FILE * file_start_pointer;
	int word_with;
	int num_words;
}ByteFile;

U8_List U8_List_init(int size);

ByteFile ByteFile_zero(void);
void U8_List_append(U8_List *list, unsigned char value);
void ByteFile_print_hex(ByteFile * bf, int n_bytes, int width);
void ByteFile_parse_command(Terminal_t *t, char * str, int len, ByteFile * bf);
int Terminal_t_parse_input(Terminal_t *t, ByteFile *bf);
ByteFile ByteFile_parse_file(FILE * fp);



int hex_char_int(char c);
int string_to_int(char * s);

void print_hex(unsigned char c);


extern unsigned char buffer[512];
extern int buf_it; 
unsigned char getc_store(FILE *fp);
	

void print_ascii(int start, int end);

#endif // SCRIPT_MANAGER_H_
