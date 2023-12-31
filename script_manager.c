#include "../tui/tui.h"
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

U8_List U8_List_init(int size)
{
	U8_List result;
	result.size = size;
	result.num_items = 0;
	result.cursor = 0;	
	result.arr = (unsigned char *) malloc(sizeof(unsigned char) * size);
	for(int i =0; i < result.size; i++)
	{
		result.arr[i] = 0;
	}
	return result;
}

ByteFile ByteFile_zero(void)
{
	ByteFile result;
	result.buffer = U8_List_init(256);
	result.buffer_size =0;
	result.buffer_cursor =0;
	result.read_cursor =0;
	result.fp = NULL;
	for(int i=0; i < 256; i++) result.file_name[i] =0;
	result.file_start_pointer = NULL;
	result.word_with =0;
	result.num_words =0;
	return result;
}
void U8_List_append(U8_List *list, unsigned char value)
{
	if(list->num_items == (list->size -1))
	{
		list->size *= 2;
		unsigned char * temp = (unsigned char *) malloc(sizeof(unsigned char) * list->size);
		for(int i =0; i <list->num_items; i++)
		{
			temp[i] = list->arr[i];
		}
		for( int i =list->num_items; i <list->size; i++)
		{
			temp[i] = 0;
		}
		free(list->arr);
		list->arr = temp;
		list->arr[list->num_items++] = value;
		return;
	}
	list->arr[list->num_items++] = value;
	return;
}

void ByteFile_print_hex(ByteFile * bf, int n_bytes, int width)
{
	int counter = 0;
	while(counter < n_bytes)
	{
		print_hex(bf->buffer.arr[bf->buffer_cursor++]);
		putchar(' ');
		if((++counter % width) == 0) putchar(10);
	}
}


void ByteFile_parse_command(Terminal_t *t, char * str, int len, ByteFile * bf)
{
	int cursor =0;
	while(cursor < len)
	{
		switch(str[cursor])
		{
			case 'f':
				cursor++;
				cursor++;
				int name_counter = 0;
				while(str[cursor] != ' ' && str[cursor] != '\n')
				{
					bf->file_name[name_counter++] = str[cursor++];
				}
				bf->file_name[name_counter] = '\0';
				return;
				break;
			case 'o':
				bf->fp = fopen(bf->file_name,"rb");
				if(!bf->fp)
				{
					printf("no such byte file found %s\n exiting\n",bf->file_name);
					exit(1);
				}
				return;
				break;
			case 'p':
				int arg1 = 0;
				int arg2 = 0;
				if(str[++cursor] == 'h')
				{
					if(str[++cursor] == ' ')
					{
						arg1 = string_to_int(&str[++cursor]);
						ByteFile_print_hex(bf,arg1,arg1);
						return;
					}else if(str[cursor++] == 'l')
					{
						arg1 = string_to_int(&str[++cursor]);
						while(str[cursor++] != ' '){}
						arg2 = string_to_int(&str[cursor]);
						ByteFile_print_hex(bf,arg1,arg2);
						return;
					}

				} else if(str[cursor] == 'a')
				{
					while(bf->buffer.arr[bf->buffer_cursor] != '\0')
					{
						putchar(bf->buffer.arr[bf->buffer_cursor++]);
					}
					return;
				}
				return;
			case 'c':
				cursor++;
				int pos = string_to_int(&str[++cursor]);
				if (pos > bf->read_cursor)
				{
					printf("cursor going beyond read scope. stop here\n");
					return;
				}
				bf->buffer_cursor = pos;
				return;
				break;
			case 'w':
				cursor++;
				cursor++;
				while((str[cursor] != '\n') && (str[cursor] != '\0'))
				{
					putchar(str[cursor++]);
				}
				return;
				break;
			case 'r':
				cursor++;
				cursor++;
				int num_read= string_to_int(&str[cursor]);
				for(int i =0; i< num_read; i++)
				{
					int temp = getc(bf->fp);
					if (temp == EOF) {
						printf("end of file reached, no more reading possible.\n"); 
						return;
					}
					U8_List_append(&(bf->buffer),temp);
					bf->read_cursor+=1;
				}
				return;
				break;
			case 'x':
				Terminal_t_destroy(NULL);
				exit(0);
			default:
				cursor++;
		}
		cursor++;
	}
}


int Terminal_t_parse_input(Terminal_t *t, ByteFile *bf)
{
	U8_List input = U8_List_init(512);
	char c ='c';
	Terminal_t_move_cursor(t,0,0);
	Terminal_t_clear_to_l_end(t);
	Terminal_t_move_cursor(t,0,1);
	for(int i =0; i<t->width; i++)
		putchar('#');
	Terminal_t_move_cursor(t,0,0);
	c = getchar();
	U8_List_append(&input,c);
	// it would be cleaner in a do while, howerver, need the timing to clear the line
	
	while(c != '\n')
	{
		c = getchar();
		U8_List_append(&input,c);
	}

	Terminal_t_move_cursor(t,0,2);
	Terminal_t_clear_to_l_end(t);
	Terminal_t_move_cursor(t,0,2);
	ByteFile_parse_command(t,&input.arr[input.cursor], input.num_items - input.cursor, bf);
	return 1;
}


ByteFile ByteFile_parse_file(FILE * fp)
{
	ByteFile bf= ByteFile_zero();

	U8_List flines = U8_List_init(256);
		
	// get first line
	do{
		U8_List_append(&flines,getc(fp));
	}while(flines.arr[flines.num_items-1] != '\n');

	// parse that line
	// TODO FIX NULLS
	ByteFile_parse_command(NULL,&flines.arr[flines.cursor], flines.num_items - flines.cursor, &bf);
	flines.cursor = flines.num_items;
	while(1)
	{
		do{
			int result = getc(fp);
			if (result == EOF) return bf;
			U8_List_append(&flines,result);
		}while(flines.arr[flines.num_items-1] != '\n');
		ByteFile_parse_command(NULL,&flines.arr[flines.cursor], flines.num_items - flines.cursor, &bf);
		flines.cursor = flines.num_items;
	}


	//TODO testing
	return bf;
}
