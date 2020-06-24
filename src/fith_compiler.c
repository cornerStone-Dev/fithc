/* fith compiler */
/* PUBLIC DOMAIN */


#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include <math.h>
#include <sys/random.h>

#include "std_types.h"

typedef struct Xoken Token;

typedef union data_s Data;

typedef union data_s {
	u8     *s;
	s64    i;
	f64    d;
	Data   *v;
	s32    fd[2];
} Data;

typedef struct context1_s{
	Data *        stk;
	Data *        stk_start;
	Data *        cstk;
	u8 *          source_code;
	u8 *          stecpot;
	u8            *last_constant;
	u8            *buffers[3];
	u8            *buffers_start[3];
	u8            *word_buff_stack[16];
	u8            *local_var_stack[16];
	FILE          *outputFile[2];
	u32           line_num;
	u32           stack_index;
	u32           wbs_index;
	u32           anon_func_count;
	u8            multiple[2];
	u8            is_customWord;
	u8            last_constant_len;
	u8            last_constant_type;
	u8            output_context;
	u8            printed_error;
	u8            word_flags;
	u8            in_case;
	u8   *scratch_pad_start;
	u32  scratch_pad_index;
	u32  scratch_pad_highWater;
	u8            file_name_buff[512];
} Context1;

typedef struct context2_s{
	Data *        Stub;
} Context2;

typedef struct context3_s{
	Data *        Stub;
} Context3;

typedef struct{
	Data *sp;
	Data tos;
} Registers;

/* function prototypes */
static void
save_function_addr(u8 *start, u64 len, u8 *addr);
static void
save_variable(u8 *start, u64 len, s64 val, u64 flags, Context1 *c);
static void
garbage_collect(u64 last_requested_size);
static void *
heap_malloc(size_t bytes) __attribute__((malloc,alloc_size(1)));
static inline s64 _fith_CMP_INT(s64 x,s64 y);
static inline void
_fith_insertionSort_s64(s64 *dsti, const size_t size);

static void
print_code(const u8 *str, u32 len)
{
	for(u32 x=0; x<len; x++){
		if(str[x]=='\000') {
			fputc ('\'', stdout);
			continue;
		}
		if(str[x]==0x04) {
			fputc ('}', stdout);
			continue;
		}
		fputc (str[x], stdout);
	}
}

static u8 *
load_file(u8 *file_name, u8 as_function)
{
	FILE *pFile;
	u8 * buffer;
	size_t fileSize, result;
	
	pFile = fopen ( (char *)file_name, "rb" );
	if (pFile==NULL) {fputs ("File error, cannot open source file\n",stderr); exit (1);}
	// obtain file size:
	fseek(pFile , 0 , SEEK_END);
	fileSize = ftell(pFile);
	rewind(pFile);
	// allocate memory to contain the whole file:
	buffer = malloc(fileSize+2);
	if (buffer == NULL) {fputs ("Memory error\n",stderr); exit (2);}
	// copy the file into the buffer:
	result = fread (buffer,1,fileSize,pFile);
	if (result != fileSize) {fputs ("Reading error\n",stderr); exit (3);}
	/* 0x03 terminate buffer, leave return in sub file */
	if (as_function){
		buffer[fileSize]=';';
		buffer[fileSize+1]=3;
	} else {
		buffer[fileSize]=3;
	}
	fclose (pFile);
	// TODO update to maybe not use garbage collector
	//save_variable(file_name, strlen((const char *)file_name), (s64)buffer);
	return (u8*)buffer;
}

#define FITH_STACK_MAX 135

/* globals */
#define DECREMENT_STACK \
if (c->stk>c->stk_start) \
{ \
	c->stk--; \
} else \
{ printf("stack underflow!!!\n"); }

#define INCREMENT_STACK \
if (c->stk<c->stk_end) \
{ \
	c->stk++; \
} else \
{ printf("stack overflow!!!\n"); }


#define STACK_CHECK(x) \
if ( (((r.sp - c->stk_start)+(x))<0)){printf("stack underflow!!!\n"); goto loop;} \
else if ((((r.sp - c->stk_start)+(x))>374)){printf("stack overflow!!!\n"); goto loop;}

//~ #define STACK_CHECK_DOWN(x) 
//~ if ( check_down(r.sp,c->stk_start, (x) ) ){ goto loop;}

//~ #define STACK_CHECK_UP(x) 
//~ if ( check_up(r.sp,c->stk_start, (x) ) ){ goto loop;}

#define STACK_CHECK_DOWN(x) 
//if ( __builtin_expect( ((c->stack_index+(x))<0), 0) ){/*printf("stack underflow!!!\n");*/ goto stack_down_print;}

#define STACK_CHECK_UP(x) 
//if ( __builtin_expect( ((c->stack_index+(x))>FITH_STACK_MAX), 0) ){/*printf("stack overflow!!!\n");*/ goto stack_up_print;}

//~ #define STACK_CHECK_DOWN_R(x) 
//~ if ( check_down(r.sp,c->stk_start, (x) ) ){  return tos;}

//~ #define STACK_CHECK_UP_R(x) 
//~ if ( check_up(r.sp,c->stk_start, (x) ) ){  return tos;}

//~ #define STACK_CHECK_DOWN_R(x) 
//~ if ( __builtin_expect( ((((s64)(r.sp - c->stk_start))+(x))<0), 0) ){/*printf("stack underflow!!!\n");*/ goto stack_down_print;}

//~ #define STACK_CHECK_UP_R(x) 
//~ if ( __builtin_expect( ((((s64)(r.sp - c->stk_start))+(x))>FITH_STACK_MAX), 0) ){/*printf("stack overflow!!!\n");*/ goto stack_up_print;}

#define STACK_CHECK_DOWN_R(x) 
//if ( __builtin_expect( ((c->stack_index+(x))<0), 0) ){printf("stack underflow!!!\n"); return r;}

#define STACK_CHECK_UP_R(x) 
//if ( __builtin_expect( ((c->stack_index+(x))>FITH_STACK_MAX), 0) ){printf("stack overflow!!!\n"); return r;}


#include "fith_avl.c"
#include "fith_data.c"
#include "fith_words.c"
#include "../tool_output/fith_lex.c"

#define DEFAULT_DIR     "c_src/"
#define MAIN_FILE     "main.c"
#define WORDS_FILE     "words.c"
#define TYPE_PROTO      "type_proto.h"
#define TYPES           "types.h"
#define FUNC_PROTO      "func_proto.h"
#define FL_STD_FILE     "fl_std.h"
#define FL_GLOBALS_FILE "globals.h"
#define INTERFACE_FILE  "interface.h"
#define INCLUDES_FILE   "includes.h"

int main(int argc, char **argv)
{
	
	unsigned char * data=0;
	unsigned char output_string[65536] = {0};
	unsigned char stringBuffer[4096] = {0};
	unsigned char *strBuff;
	Data stack[FITH_STACK_MAX+1]={0};
	Data cstack[128]={0};
	//u8 dirName[512];
	
	u32 x;
	Context1 c = {0};
	Context2 c2 = {0};
	Registers r = {0};
	//FILE * pFile;
	//DIR *d=0;
	//struct dirent *dir;
	r.sp = stack;
	c.stk = stack;
	c.stk_start = stack;
	c.cstk = cstack;
	c.line_num = 1;
	strBuff = stringBuffer;
	
	var_data.v = malloc(4096);
	var_data.hw=511;
	
	heap_data.c = &c;
	heap_data.h = malloc(128*1024*1);
	heap_data.t=(128*1024*1)-1;
	heap_data.cache=(u8*)5; // set to garbage
	
	c.buffers[0] = malloc(128*1024*1);
	c.buffers_start[0] = c.buffers[0];
	c.buffers[1] = malloc(128*1024*1);
	c.buffers_start[1] = c.buffers[1];
	c.buffers[2] = output_string;
	c.buffers_start[2] = output_string;
	c.multiple[0] = 1;
	c.multiple[1] = 1;
	
	strBuff = (u8*)stpcpy((char *)stringBuffer, DEFAULT_DIR);
	
	u32 i=1;

	for (; i<argc; i++)
	{
		x = lex_options((u8 *)argv[i]);
		
		switch (x){
			case 0:
			return 0;
			case 1:
			strBuff = (u8*)stpcpy((char *)stringBuffer, &argv[1][2]);
			strBuff = (u8*)stpcpy((char *)strBuff, "/");
			break;
			case 2:
			strcpy((char *)strBuff, MAIN_FILE);
			c.outputFile[0] = fopen ( (const char *)stringBuffer, "w" );
			if (c.outputFile[0]==NULL) {fputs ("File error",stderr); exit (1);}
			strcpy((char *)strBuff, WORDS_FILE);
			c.outputFile[1] = fopen ( (const char *)stringBuffer, "w" );
			if (c.outputFile[1]==NULL) {fputs ("File error",stderr); exit (1);}
			fwrite (MAIN_OPEN,
			sizeof(char),
			strlen(MAIN_OPEN),
			c.outputFile[0]);
			fwrite ("// fith compiler output\n\n",
			sizeof(char),
			strlen("// fith compiler output\n\n"),
			c.outputFile[1]);
			printf("target file: %s\n",argv[i]);
			sprintf((char *)c.file_name_buff, "%s", argv[i]);
			data = load_file(c.file_name_buff, 0);
			c.source_code = data;
			r = lex(&c, r, &c2);
			break;
		}
	}
	
	if(c.outputFile[0]){
		fwrite(c.buffers_start[0],
				sizeof(char),
				c.buffers[0]-c.buffers_start[0],
				c.outputFile[0]);
		fwrite (MAIN_CLOSE,
			sizeof(char),
			strlen(MAIN_CLOSE),
			c.outputFile[0]);
		fflush (c.outputFile[0]); 
		fclose (c.outputFile[0]);
	}
	
	if(c.outputFile[1]){
		fwrite(c.buffers_start[1],
				sizeof(char),
				c.buffers[1]-c.buffers_start[1],
				c.outputFile[1]);
		fflush (c.outputFile[1]); 
		fclose (c.outputFile[1]);
	}
	
	s32 rcode;
	if(c.printed_error){
		rcode = 1;
	} else {
		rcode = 0;
	}
	return rcode;
}
