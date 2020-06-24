/* new standard types */
/* fith compiler */
/* PUBLIC DOMAIN */

typedef uint8_t  u8;
typedef int8_t   s8;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint64_t u64;
typedef int64_t  s64;
typedef float    f32;
typedef double   f64;

#define alignOf  _Alignof
#define bool     _Bool
#define atomic   _Atomic
#define noReturn _Noreturn
#define alignAs  _Alignas

// TODO Test is Restrict is better code gen...

#define MAIN_OPEN \
"// fith compiler output\n\n" \
"#include <stdio.h>\n" \
"#include <stdlib.h>\n" \
"#include <string.h>\n" \
"#include <stdint.h>\n" \
"#include <dirent.h>\n" \
"#include <sys/types.h>\n" \
"#include <unistd.h>\n" \
"#include <sys/socket.h>\n" \
"#include <time.h>\n" \
"#include <math.h>\n" \
"#include <sys/random.h>\n" \
"typedef uint8_t  u8;\n" \
"typedef int8_t   s8;\n" \
"typedef uint16_t u16;\n" \
"typedef int16_t  s16;\n" \
"typedef uint32_t u32;\n" \
"typedef int32_t  s32;\n" \
"typedef uint64_t u64;\n" \
"typedef int64_t  s64;\n" \
"typedef float    f32;\n" \
"typedef double   f64;\n" \
"#define alignOf  _Alignof\n" \
"#define bool     _Bool\n" \
"#define atomic   _Atomic\n" \
"#define noReturn _Noreturn\n" \
"#define alignAs  _Alignas\n" \
"typedef union data_s Data;\n" \
"typedef union data_s {\n" \
"	u8     *s;\n" \
"	s64    i;\n" \
"	f64    d;\n" \
"	Data   *v;\n" \
"	s32    fd[2];\n" \
"} Data;\n" \
"typedef struct context1_s{\n" \
"	Data * restrict stk_start;\n" \
"	u8   *scratch_pad_start;\n" \
"	u32  scratch_pad_index;\n" \
"	u32  scratch_pad_highWater;\n" \
"} Context1;\n" \
"typedef struct{\n" \
"	Data * restrict sp;\n" \
"	Data tos;\n" \
"} Registers;\n" \
"typedef struct{\n" \
"	Data stack[136];\n" \
"	Context1 context;\n" \
"} MainMemory;\n" \
"#include \"../src/fith_words.c\"\n" \
"#include \"words.c\"\n" \
"int main(int argc, char **argv)\n" \
"{\n" \
"alignAs(64) MainMemory mm;\n" \
"Context1 * restrict c=&mm.context;\n" \
"Registers r;\n" \
"r.sp=&mm.stack[0];\n" \
"r.tos.i=0;\n" \
"mm.context.stk_start=&mm.stack[0];\n" \
"mm.context.scratch_pad_index=0;\n" \
"mm.context.scratch_pad_highWater=(128*1024*1)-1;\n" \
"mm.context.scratch_pad_start=malloc(128*1024*1);\n" \


#define MAIN_CLOSE \
"}\n" \





