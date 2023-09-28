typedef struct
{
	int size;
	int num_items;
	int cursor;
	unsigned char * arr;
} U8_List;
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
} ByteFile;

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
		if((counter++ % width) == 0) putchar(10);
		print_hex(bf->buffer.arr[bf->buffer_cursor++]);
		putchar(' ');
	}
}


void parse_command(char * str, int len, ByteFile * bf)
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
			default:
				cursor++;
		}
		cursor++;
	}
}




ByteFile parse_file(FILE * fp)
{
	// split into lines?
	// yes
	ByteFile bf= ByteFile_zero();;	
	U8_List lines = U8_List_init(256);
		
	// get first line
	do{
		U8_List_append(&lines,getc(fp));
	}while(lines.arr[lines.num_items-1] != '\n');

	// parse that line
	parse_command(&lines.arr[lines.cursor], lines.num_items - lines.cursor, &bf);
	lines.cursor = lines.num_items;
	while(1)
	{
		do{
			int result = getc(fp);
			if (result == EOF) return bf;
			U8_List_append(&lines,result);
		}while(lines.arr[lines.num_items-1] != '\n');
		parse_command(&lines.arr[lines.cursor], lines.num_items - lines.cursor, &bf);
		lines.cursor = lines.num_items;
	}


	//TODO testing
	//TODO implement more than one line
	return bf;
}
