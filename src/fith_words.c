/* fith words */

typedef Registers (*Fith_Func)(Context1 *c, Registers r);

static inline Registers
_fith_push(Context1 *c, Registers r, Data val) __attribute__((always_inline));
static inline Registers
_fith_push_i(Context1 *c, Registers r, s64 i) __attribute__((always_inline));
static inline Registers
_fith_push_d(Context1 *c, Registers r, f64 d) __attribute__((always_inline));
static inline Registers
_fith_push_s(Context1 *c, Registers r, u8 *s) __attribute__((always_inline));
static inline Registers
_fith_bitwise_and(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_bitwise_or(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_equals(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_not_equals(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_equalsf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_not_equalsf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_less_than(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_greater_than(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_less_than_or_equals(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_greater_than_or_equals(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_less_thanf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_greater_thanf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_less_than_or_equalsf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_greater_than_or_equalsf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_shift_left(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_shift_right(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_add(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_sub(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_divi(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_mul(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_addf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_subf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_divif(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_mulf(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_modulo(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_modulof(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_bitwise_not(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_print_stack(Context1 *c, Registers r);
static Registers
_fith_print_stackf(Context1 *c, Registers r);
static inline Registers
_fith_print_string(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_logical_or(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_logical_and(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_logical_not(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_pick_number(Context1 *c, Registers r, u64 num) __attribute__((always_inline));
static inline Registers
_fith_dup(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_dep(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_rot(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_abs(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_i2s(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_f2s(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_s2i(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_s2f(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_rev(Context1 *c, Registers r);
static inline Registers
_fith_over(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_pick(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_drop(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_swap(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_sort(Context1 *c, Registers r);
static inline Registers
_fith_fabs(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_chan(Context1 *c, Registers r);
static inline Registers
_fith_clear(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_sleep(Context1 *c, Registers r);
static Registers
_fith_array(Context1 *c, Registers r);
static Registers
_fith_malloc(Context1 *c, Registers r);
static inline Registers
_fith_free(Context1 *c, Registers r) __attribute__((always_inline));
static Registers
_fith_random(Context1 *c, Registers r);
static Registers
_fith_realloc(Context1 *c, Registers r);
static inline Registers
_fith_array_get(Context1 *c, Registers r) __attribute__((always_inline));
static inline Registers
_fith_array_set(Context1 *c, Registers r) __attribute__((always_inline));
static void *
_fith_scratchPad_alloc(Context1 *c, size_t bytes);
static Registers
_fith_loadf(Context1 *c, Registers r);
static Registers
_fith_fork(Context1 *c, Registers r);
static inline Registers
_fith_call(Context1 *c, Registers r)__attribute__((always_inline));
static Registers
_fith_writes(Context1 *c, Registers r);
static Registers
_fith_reads(Context1 *c, Registers r);
static Registers
_fith_memcmp(Context1 *c, Registers r);


static Registers
_fith_memcmp(Context1 *c, Registers r)
{
	r.sp-=2;
	s32 res = memcmp(r.sp->s,
					(r.sp+1)->s,
					r.tos.i);
	r.tos.i=res;
	return r;
}

static Registers
_fith_reads(Context1 *c, Registers r)
{
	r.sp-=2;
	s32 tmp = read(r.sp->i, (r.sp+1)->s, r.tos.i);
	if (tmp < 0)
	{
		printf("reads error!!!\n");
	}
	r.tos.s = (r.sp+1)->s;
	return r;
}

static Registers
_fith_writes(Context1 *c, Registers r)
{
	r.sp-=2;
	s32 res;
	res = write((r.sp+1)->i,
				r.tos.s,
				strlen((const char *)r.tos.s)+1);
	r.tos.i = r.sp->i;
	if (res < 0)
	{
		printf("writes error!!!\n");
	}
	return r;
}

static inline Registers
_fith_call(Context1 *c, Registers r)
{
	Fith_Func func = (Fith_Func)r.tos.i;
	r = _fith_drop(c,r); 
	return (*func)(c,r);
}

static Registers
_fith_fork(Context1 *c, Registers r)
{
	
	Fith_Func func = (Fith_Func)r.tos.i;
	s32 res = fork();
	if (res < 0){
		printf("Fork error!!!\n");
	} else if (res == 0) {
		r = _fith_drop(c,r);
		r=(*func)(c,r);
		_Exit(r.tos.i);
	} else {
		r.tos.i = res;
	}
	return r;
}

static Registers
_fith_loadf(Context1 *c, Registers r)
{
	FILE *pFile;
	u8   *buffer;
	size_t fileSize, result;
	
	pFile = fopen ( (char *)r.tos.s, "rb" );
	if (pFile==NULL) {fputs ("_fith_loadf: File error, cannot open source file\n",stderr); exit(1);}
	// obtain file size:
	fseek(pFile , 0 , SEEK_END);
	fileSize = ftell(pFile);
	rewind(pFile);
	// allocate memory to contain the whole file:
	buffer = malloc(fileSize+1);
	if (buffer == NULL) {fputs ("_fith_loadf: Memory error\n",stderr); exit (2);}
	// copy the file into the buffer:
	result = fread (buffer,1,fileSize,pFile);
	if (result != fileSize) {fputs ("_fith_loadf: Reading error\n",stderr); exit (3);}
	/* null terminate buffer */
	buffer[fileSize]=0;
	fclose (pFile);
	r.tos.s = buffer;
	
	return r;
}

static struct PrngType{
  u32 produce_count;          /* True if initialized */
  u8 i, j;            /* State variables */
  u8 s[256];          /* State variables */
} Prng;

static void 
_fith_randomness_init(void)
{
	u32 i;
	s32 res;
	u8 k[256];
	u8 t;
	Prng.j = 0;
	Prng.i = 0;
	do{
		res = getrandom(&k, 256, 0);
	} while(res!=256);
	for(i=0; i<256; i++){
		Prng.s[i] = (u8)i;
	}
	for(i=0; i<256; i++){
		Prng.j += Prng.s[i] + k[i];
		t = Prng.s[Prng.j];
		Prng.s[Prng.j] = Prng.s[i];
		Prng.s[i] = t;
	}
}

/*
** Return N random bytes.
*/
static void 
_fith_randomness(u32 N, void *pBuf)
{
	u8 *zBuf = pBuf;
	u8 t;

	if( (Prng.produce_count&0x3FFFFFFF)==0 )
	{
		_fith_randomness_init();
	}
	Prng.produce_count+=N;

	do{
		Prng.i++;
		t = Prng.s[Prng.i];
		Prng.j += t;
		Prng.s[Prng.i] = Prng.s[Prng.j];
		Prng.s[Prng.j] = t;
		t += Prng.s[Prng.i];
		*(zBuf++) = Prng.s[t];
	}while( --N );
}

static inline
s64 _fith_CMP_INT(s64 x,s64 y)
{
	return ((s64)(((u64)(x))-((u64)(y))));
}

/*  Used in mergesort. */
static inline void
_fith_insertionSort_s64(s64 *dsti, const size_t size) 
{
	size_t i=0;
	s64 *dst=dsti;
	
	do{
		size_t j;
		s64 x;
        i++;
		/* If this entry is already correct, just move along */
		if (_fith_CMP_INT(dst[i - 1], dst[i]) <= 0)
		{
			continue;
		}

		/* Else we need to find the right place while shifting everything over */
		x = dst[i];
		j = i;

		for (;;) 
		{
			dst[j] = dst[j-1];
			j--;
			if ( ((j == 0)||(_fith_CMP_INT(dst[j-1], x) <= 0)) )
			{
				break;
			}
		}
		dst[j] = x;
	} while( (i+1) < size );
}

// scratchpad is a circular buffer, return next slot
static void *
_fith_scratchPad_alloc(Context1 *c, size_t bytes)
{
	void *p;
	u64 next_index;
	
	// round bytes up to nearest multiple of 8
	bytes=(bytes+7)/8*8;
	next_index = c->scratch_pad_index+bytes;
	 // test if scratchpad is full
	if(next_index>c->scratch_pad_highWater)
	{
		// scratchpad is full, reset to start
		c->scratch_pad_index = 0;
		next_index = c->scratch_pad_index+bytes;
	}
	// return pointer in next consequtive slot open
	p = &c->scratch_pad_start[c->scratch_pad_index];
	c->scratch_pad_index = next_index;
	return p;
}

static inline Registers
_fith_push(Context1 *c, Registers r, Data val)
{
	*r.sp = r.tos;
	r.tos = val;
	r.sp++;
	return r;
}

static inline Registers
_fith_push_i(Context1 *c, Registers r, s64 i)
{
	r.sp->i = r.tos.i;
	r.tos.i = i;
	r.sp++;
	return r;
}

static inline Registers
_fith_push_d(Context1 *c, Registers r, f64 d)
{
	r.sp->i = r.tos.i;
	r.tos.d = d;
	r.sp++;
	return r;
}

static inline Registers
_fith_push_s(Context1 *c, Registers r, u8 *s)
{
	r.sp->i = r.tos.i;
	r.tos.s = s;
	r.sp++;
	return r;
}

static inline Registers
_fith_bitwise_and(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i&r.tos.i;
	return r;
}

static inline Registers
bitwise_xor(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i^r.tos.i;
	return r;
}

static inline Registers
_fith_bitwise_or(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i|r.tos.i;
	return r;
}

static inline Registers
_fith_equals(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i==r.tos.i;
	return r;
}

static inline Registers
_fith_not_equals(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i!=r.tos.i;
	return r;
}

static inline Registers
_fith_equalsf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d==r.tos.d;
	return r;
}

static inline Registers
_fith_not_equalsf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d!=r.tos.d;
	return r;
}

static inline Registers
_fith_less_than(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i<r.tos.i;
	return r;
}

static inline Registers
_fith_greater_than(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i>r.tos.i;
	return r;
}

static inline Registers
_fith_less_than_or_equals(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i<=r.tos.i;
	return r;
}

static inline Registers
_fith_greater_than_or_equals(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i>=r.tos.i;
	return r;
}

static inline Registers
_fith_less_thanf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d<r.tos.d;
	return r;
}

static inline Registers
_fith_greater_thanf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d>r.tos.d;
	return r;
}

static inline Registers
_fith_less_than_or_equalsf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d<=r.tos.d;
	return r;
}

static inline Registers
_fith_greater_than_or_equalsf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d>=r.tos.d;
	return r;
}

static inline Registers
_fith_shift_left(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i<<r.tos.i;
	return r;
}

static inline Registers
_fith_shift_right(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i>>r.tos.i;
	return r;
}

static inline Registers
_fith_add(Context1 *c, Registers r)
{
	r.sp--;
	//r.tos.i = r.sp->i+r.tos.i;
	r.tos.i = (s64)(((u64)r.sp->i)+((u64)r.tos.i));
	return r;
}

static inline Registers
_fith_sub(Context1 *c, Registers r)
{
	r.sp--;
	//r.tos.i = r.sp->i-r.tos.i;
	r.tos.i = (s64)(((u64)r.sp->i)-((u64)r.tos.i));
	return r;
}

static inline Registers
_fith_divi(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i/r.tos.i;
	return r;
}

static inline Registers
_fith_mul(Context1 *c, Registers r)
{
	r.sp--;
	//r.tos.i = r.sp->i*r.tos.i;
	r.tos.i = (s64)(((u64)r.sp->i)*((u64)r.tos.i));
	return r;
}

static inline Registers
_fith_addf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d+r.tos.d;
	return r;
}

static inline Registers
_fith_subf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d-r.tos.d;
	return r;
}

static inline Registers
_fith_divif(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d/r.tos.d;
	return r;
}

static inline Registers
_fith_mulf(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.d = r.sp->d*r.tos.d;
	return r;
}

static inline Registers
_fith_modulo(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i%r.tos.i;
	return r;
}

static inline Registers
_fith_modulof(Context1 *c, Registers r)
{
	f64 var;	
	r.sp--;
	var = r.sp->d/r.tos.d;
	var = modf(var, &r.sp->d);
	r.tos.d = var * r.tos.d;
	return r;
}

static Registers
_fith_print_stack(Context1 *c, Registers r)
{
	u32 x=1;
	if(&c->stk_start[0]<r.sp){
		for(; &c->stk_start[x]!=r.sp;x++){
			printf("(%ld) ",c->stk_start[x].i);
		}
		printf("(%ld) \n",r.tos.i);
	}
	return r;
}

static Registers
_fith_print_stackf(Context1 *c, Registers r)
{
	u32 x=1;
	if(&c->stk_start[0]<r.sp){
		for(; &c->stk_start[x]!=r.sp;x++){
			printf("(%f) ",c->stk_start[x].d);
		}
		printf("(%f) \n",r.tos.d);
	}
	return r;
}

static inline Registers
_fith_bitwise_not(Context1 *c, Registers r)
{
	r.tos.i = ~r.tos.i;
	return r;
}

static inline Registers
_fith_print_string(Context1 *c, Registers r)
{
	r.sp--;
	printf("%s\n",(const char *)r.tos.s);
	r.tos.i = r.sp->i;
	return r;
}

static inline Registers
_fith_logical_or(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i||r.tos.i;
	return r;
}

static inline Registers
_fith_logical_and(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i&&r.tos.i;
	return r;
}

static inline Registers
_fith_logical_not(Context1 *c, Registers r)
{
	r.tos.i = !r.tos.i;
	return r;
}

static inline Registers
_fith_pick_number(Context1 *c, Registers r, u64 num)
{
	r.sp->i = r.tos.i;
	r.tos.i = (r.sp-num)->i;
	r.sp++;
	return r;
}

static inline Registers
_fith_dup(Context1 *c, Registers r)
{
	//_fith_pick_number(c,r,0); compiler would barf on this
	r.sp->i = r.tos.i;
	r.sp++;
	return r;
}

static inline Registers
_fith_dep(Context1 *c, Registers r)
{
	r.sp->i = r.tos.i;
	r.tos.i = r.sp - c->stk_start;
	r.sp++;
	return r;
}

static inline Registers
_fith_rot(Context1 *c, Registers r)
{
	s64 tmp;	
	tmp = (r.sp-2)->i;
	(r.sp-2)->i = (r.sp-1)->i;
	(r.sp-1)->i = r.tos.i;
	r.tos.i = tmp;
	return r;
}

static inline Registers
_fith_abs(Context1 *c, Registers r)
{
	r.tos.i=labs(r.tos.i);
	return r;
}

static inline Registers
_fith_i2s(Context1 *c, Registers r)
{
	// save off value
	s64 tmp=r.tos.i;
	// get string
	r.tos.s = _fith_scratchPad_alloc(c,24);
	sprintf((char *)r.tos.s, "%ld", tmp);
	return r;
}

static inline Registers
_fith_f2s(Context1 *c, Registers r)
{
	// save off value
	f64 tmp=r.tos.d;
	// get string
	r.tos.s = _fith_scratchPad_alloc(c,24);
	sprintf((char *)r.tos.s, "%f", tmp);
	return r;
}

static inline Registers
_fith_s2i(Context1 *c, Registers r)
{
	r.tos.i = strtol( (const char *)r.tos.s, NULL, 0);
	return r;
}

static inline Registers
_fith_s2f(Context1 *c, Registers r)
{
	r.tos.d = atof( (const char *)r.tos.s );
	return r;
}

static Registers
_fith_rev(Context1 *c, Registers r)
{
	s64 tmp, num;
	s64 *start, *end;	
	num = r.tos.i;
	start = (s64 *)r.sp - num;
	end = (s64 *)r.sp - 1;
	// reverse items
	while(start<end){
		tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
	r.sp-=1;
	r.tos.i = r.sp->i;
	return r;
}

static inline Registers
_fith_over(Context1 *c, Registers r)
{
	r.sp->i = r.tos.i;
	r.tos.i = (r.sp-1)->i;
	r.sp++;
	return r;
}

static inline Registers
_fith_pick(Context1 *c, Registers r)
{
	r.sp->i = r.tos.i;
	r.tos.i = (r.sp-2)->i;
	r.sp++;
	return r;
}

static inline Registers
_fith_drop(Context1 *c, Registers r)
{
	r.sp--;
	r.tos.i = r.sp->i;
	return r;
}

static inline Registers
_fith_swap(Context1 *c, Registers r)
{
	s64 tmp;	
	tmp = (r.sp-1)->i;
	(r.sp-1)->i = r.tos.i;
	r.tos.i = tmp;
	return r;
}

static Registers
_fith_sort(Context1 *c, Registers r)
{
	s64 num;	
	// TODO TEST
	num = r.tos.i;
	if(num>1){
		_fith_insertionSort_s64((s64 *)(r.sp-num), num);
	}
	r.sp-=1;
	r.tos.i = r.sp->i;
	return r;
}

static inline Registers
_fith_fabs(Context1 *c, Registers r)
{
	r.tos.d=fabs(r.tos.d);
	return r;
}

static Registers
_fith_chan(Context1 *c, Registers r)
{
	s32 res = socketpair(AF_UNIX, SOCK_STREAM, 0, (r.sp+2)->fd);
	if (res < 0)
	{
		printf("socketpair error!!!\n");
	} else {
		r.sp->i = r.tos.i;
		(r.sp+1)->i = (r.sp+2)->fd[0];
		r.tos.i = (r.sp+2)->fd[1];
		r.sp+=2;
	}
	return r;
}

static inline Registers
_fith_clear(Context1 *c, Registers r)
{
	r.sp=c->stk_start;
	return r;
}

static Registers
_fith_sleep(Context1 *c, Registers r)
{
	struct timespec time;
	r.sp-=2;
	time.tv_sec = (r.sp+1)->i;
	time.tv_nsec = r.tos.i;
	r.tos.i = r.sp->i;
	nanosleep(&time, NULL);
	return r;
}

static Registers
_fith_array(Context1 *c, Registers r)
{
	// allocate array, 8 byte header
	u64 tmp = r.tos.i*8+8;
	r.tos.s= malloc(tmp);
	if (r.tos.s == 0 )
	{
		printf("malloc error!!!\n");
	}
	r.tos.v->i = tmp>>3;
	return r;
}

static inline Registers
_fith_array_get(Context1 *c, Registers r)
{
	r.sp-=1;
	r.tos = r.tos.v[r.sp->i+1];
	return r;
}

static inline Registers
_fith_array_set(Context1 *c, Registers r)
{
	r.sp-=3;
	r.tos.v[(r.sp+2)->i+1] = *(r.sp+1);
	r.tos = *r.sp;
	return r;
}

static inline Registers
_fith_array_len(Context1 *c, Registers r)
{
	r.tos.i = r.tos.v->i-1;
	return r;
}

static Registers
_fith_malloc(Context1 *c, Registers r)
{
	r.tos.s= malloc(r.tos.i);
	if (r.tos.s == 0 )
	{
		printf("malloc error!!!\n");
	}
	return r;
}

static inline Registers
_fith_free(Context1 *c, Registers r)
{
	free(r.tos.s);
	return _fith_drop(c,r);
}

static Registers
_fith_random(Context1 *c, Registers r)
{
	r.sp->i = r.tos.i;
	_fith_randomness(8, &r.tos.i);
	r.sp++;
	return r;
}

static Registers
_fith_realloc(Context1 *c, Registers r)
{
	void *ptr;
	r.sp--;
	ptr= realloc(r.sp->s, r.tos.i);
	if (ptr == 0)
	{
		printf("realloc error, allocation unchanged!\n");
		r.tos.s = r.sp->s;
		return r;
	}
	r.tos.s = ptr;
	return r;
}

