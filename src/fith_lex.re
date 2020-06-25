/* fith compiler */
/* PUBLIC DOMAIN */


/*!max:re2c*/                        // directive that defines YYMAXFILL (unused)
/*!re2c                              // start of re2c block
	
	mcm = "(" [^)\x03]* ")"; 
	scm = "\\" [^\n\x03]* "\n";
	wsp = ([ \n\t\r] | scm | mcm)+; // removed \v
	//macro = "#" ([^\n] | "\\\n")* "\n";
	// integer literals
	oct = "0" [0-7]*;
	dec = [1-9][0-9]*;
	hex = "0x" [0-9A-F]+; // a-f removed
	// floating literals
	frc = [0-9]* "." [0-9]+ | [0-9]+ ".";
	exp = 'e' [+-]? [0-9]+;
	flt = "-"? (frc exp? | [0-9]+ exp) [fFlL]?;
	string_lit = ['] ([^'\x00\x03] | ([\\] [']))* ['];
	//string_lit_chain = string_lit ([ \n\t\r]* string_lit)+;
	//string_lit_chain = ([^"\n] | ([\\] ["]))* ("\n" | ["]);
	string_lit_chain = ([^'\n] | ([\\] [']))* "\n";
	string_lit_end = ([^'\n] | ([\\] [']))* ['];
	mangled_string_lit = ['] ([^'\x00\x03] | ([\\] [']))* "\x00";
	char_lit = [`] ([^`\x03] | ([\\] [`]))* [`];
	integer = "-"? (oct | dec | hex);
	word = [a-zA-Z_]([a-zA-Z_0-9?!#.{}[-]|"]"|"^")*;
	function_call_addr = "@" word ;
	function_definition = word ":";
	goto_jump = word ":>";
	goto_label = word "<:";
	var = "$" word; // push value on stack, if exists
	var_assign = "=$" word; // pop top of stack and assign to value, create variable
	var_addr = "@$" word; // push address on stack

	
*/                                   // end of re2c block


static int lex_options(/*const*/ u8 * YYCURSOR) // YYCURSOR is defined as a function parameter
{                                    //
	u8 * YYMARKER;    // YYMARKER is defined as a local variable
	//const u8 * YYCTXMARKER; // YYCTXMARKER is defined as a local variable
	/*const*/ //u8 * YYCURSOR;    // YYCURSOR is defined as a local variable
	/*const*/ u8 * start;
	
	//YYCURSOR = *YYCURSOR_p;

//loop: // label for looping within the lexxer
	start = YYCURSOR;

	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { printf("Invalid Option: %s, Operation aborted\n",start); return 0; } //   default rule with its semantic action
	[\x00] { return 0; }             // EOF rule with null sentinal
	
	"-d"[a-zA-Z_/0-9]+ {
		return 1;
	}
	
	//[a-zA-Z_/0-9-]+ ".fith" {
	[a-zA-Z_/0-9] [a-zA-Z_/0-9-]* ".fith" {
		return 2;
	}
	
	*/                               // end of re2c block
}

static int lex_string_lit_chain(u8 ** YYCURSOR_p)
{                                    //
	u8 * YYCURSOR;
	u8 *start;
	u8 *startMangledString;
	u64 len;
	YYCURSOR = *YYCURSOR_p;
	startMangledString = YYCURSOR;
	

loop: // label for looping within the lexxer
	start = YYCURSOR;

	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { goto loop; }//   default rule with its semantic action
	//[\x00] { return 1; }             // EOF rule with null sentinal
	
	string_lit_chain {
		len = YYCURSOR-start-1;
		memmove(startMangledString, start, len);
		startMangledString+=len;
		// skip starting tabs to allow formatting
		while(*YYCURSOR=='\t'){YYCURSOR++;}
		goto loop;
	}
	
	string_lit_end {
		if(startMangledString==start)
		{
			*(YYCURSOR-1) = 0;
			return 0;
		}
		len = YYCURSOR-start-1;
		memmove(startMangledString, start, len);
		startMangledString+=len;
		*startMangledString=0;
		*YYCURSOR_p = startMangledString;
		return 1;
	}

	*/                               // end of re2c block
}

static u64 lex_if_else(/*const*/ u8 ** YYCURSOR_p, u32 is_else, u32 in_case) // YYCURSOR is defined as a function parameter
{                                    //
	u8 *YYMARKER;    // YYMARKER is defined as a local variable
	//const u8 * YYCTXMARKER; // YYCTXMARKER is defined as a local variable
	/*const*/ u8 *YYCURSOR;    // YYCURSOR is defined as a local variable
	u8 *start;
	u8 *finish;
	u32 word_len=0;
	u32 num_ifs=0;
	u32 num_funcs=0;
	u32 num_loops=0;
	u32 num_case=0;
	
	YYCURSOR = *YYCURSOR_p;

loop: // label for looping within the lexxer
	start = YYCURSOR;
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { goto loop; }//   default rule with its semantic action
	[\x03] { return 1; }             // EOF rule with null sentinal
	
	
	(scm | mcm)+ {
		goto loop;
	}
	
	string_lit {
		goto loop;
	}
	
	mangled_string_lit {
		goto loop;
	}
	
	":" {
		num_funcs++;
		goto loop;
	}
	
	";" {
		if ( (is_else==2) && (num_funcs==0) ){
			*YYCURSOR_p = YYCURSOR;
			return 0;
		}
		num_funcs--;
		goto loop;
	}

	"}" {
		if (num_ifs==0 && ((is_else==0)||(is_else==1)) ){
			if(in_case){
				*(YYCURSOR-1)=0x04;
			}
			*YYCURSOR_p = YYCURSOR;
			return 0;
		}
		num_ifs--;
		goto loop;
	}

	word {
		word_len = YYCURSOR-start;
		finish = YYCURSOR;
		goto word_processing;
	}

	*/                               // end of re2c block
	
	word_processing:
	switch(word_len){
	case 2: // 2 letter words
	YYCURSOR = start;
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		YYCURSOR = finish;
		goto loop;
	}

	"do" {
		num_loops++;
		goto loop;
	}
	*/                               // end of re2c block
	break;
	case 3: // 3 letter words
	YYCURSOR = start;
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		YYCURSOR = finish;
		goto loop;
	}

	"end" {
		if ( (is_else==4) && (num_case==0) ){
			*YYCURSOR_p = YYCURSOR;
			return 0;
		}
		num_case--;
		goto loop;
	}
	"if{" {
		num_ifs++;
		goto loop;
	}
	*/                               // end of re2c block
	break;
	case 4: // 4 letter words
	YYCURSOR = start;
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		YYCURSOR = finish;
		goto loop;
	}

	"loop" {
		if ( (is_else==3) && (num_loops==0) ){
			*YYCURSOR_p = YYCURSOR;
			return 0;
		}
		num_loops--;
		goto loop;
	}
	"case" {
		num_case++;
		goto loop;
	}
	"else" {
		if ( (num_ifs==0) && (is_else==0) ){
			*YYCURSOR_p = YYCURSOR;
			return 0;
		}
		goto loop;
	}
	*/                               // end of re2c block
	break;
	default: goto loop;
	}
}

// sub-lexxer for dealing with word.
static Registers lex_word(Context1 *c, Registers r, u8 **YYCURSORout, u64 len) // YYCURSOR is defined as a function parameter
{                                    //
	u8 * YYMARKER;    // YYMARKER is defined as a local variable
	//const u8 * YYCTXMARKER; // YYCTXMARKER is defined as a local variable
	u8 * YYCURSOR;    // YYCURSOR is defined as a local variable
	//u8 * start;
	
	c->is_customWord =0;
	YYCURSOR = c->source_code;

//loop: // label for looping within the lexxer
	//start = YYCURSOR;
	
	switch(len-1){
	case 0: // 1 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"p" {
		STACK_CHECK_DOWN_R(-1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_print_string(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	*/                               // end of re2c block
	break;
	case 1: // 2 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"or" { // "||"
		STACK_CHECK_DOWN_R(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_logical_or(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"do" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"while(1){");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	*/                               // end of re2c block
	break;
	case 2: // 3 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"and" { // "&&"
		STACK_CHECK_DOWN_R(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_logical_and(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"not" {
		STACK_CHECK_DOWN_R(-1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_logical_not(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"dup" {
		STACK_CHECK_DOWN_R(-1)
		STACK_CHECK_UP_R(1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_dup(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"dep" {
		STACK_CHECK_UP_R(1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_dep(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"rot" {
		STACK_CHECK_DOWN_R(-3)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_rot(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"abs" {
		STACK_CHECK_DOWN_R(-1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_abs(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"i2f" {
		STACK_CHECK_DOWN_R(-1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r.tos.d=r.tos.i;");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"f2i" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r.tos.i=r.tos.d;");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"i2s" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_i2s(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"f2s" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_f2s(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"s2i" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_s2i(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"s2f" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_s2f(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"rev" {
		STACK_CHECK_DOWN_R(-1)
		//~ if( (r.sp - c->stk_start-1) < r.tos.i ){
			//~ printf("rev : stack underflow avoided!!!\n");
			//~ return r;
		//~ }
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_rev(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"if{" {
		STACK_CHECK_DOWN_R(-1)

		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			if(c->in_case){
				c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					//"{if(tmp.i){");
					"{Data _fith_tmp=r.tos;r=_fith_drop(c,r);if(_fith_tmp.i){");
				// re-write ending for case statement
				lex_if_else(&YYCURSOR, 0, 1);
				c->in_case=0;
			} else {
				c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"{Data _fith_tmp=r.tos;r=_fith_drop(c,r);if(_fith_tmp.i){");
			}
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"end" {
		// clear flag
		c->in_case=0;
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"break;}while(1);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	*/                               // end of re2c block
	break;
	case 3: // 4 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"call" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_call(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	//~ "load" {
		//~ STACK_CHECK_DOWN_R(-1)
		//~ r.sp--;
		//~ u8 *tmp = load_file(r.tos.s,1);
		//~ r.tos.i = r.sp->i;
		//~ // save off return in command stack
		//~ c->cstk->s = YYCURSOR;
		//~ c->cstk++;
		//~ *YYCURSORout = tmp;
		//~ return r;
	//~ }
	"over" {
		STACK_CHECK_DOWN_R(-2)
		STACK_CHECK_UP_R(1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_over(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"pick" {
		STACK_CHECK_DOWN_R(-3)
		STACK_CHECK_UP_R(1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_pick(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"drop" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_drop(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"swap" {
		STACK_CHECK_DOWN_R(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_swap(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"else" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"}else{");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"fork" {
		// fork executes a function in another process. The parent process will
		// skip the next function call. The child process need to have the
		// return stack modified to exit, returns pid
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_fork(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"exit" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"_Exit(r.tos.i);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"free" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_free(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"sort" {
		STACK_CHECK_DOWN_R(-1)
		//~ if( (r.sp - c->stk_start) < r.tos.i ){
			//~ printf("stack underflow avoided!!!\n");
			//~ return r;
		//~ }
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_sort(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"fabs" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_fabs(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"chan" {
		STACK_CHECK_UP_R(2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_chan(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"loop" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"}");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"case" {
		// duplicate test value if there
		STACK_CHECK_DOWN_R(-1)
		STACK_CHECK_UP_R(1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"do{Data _fith_tmp=r.tos;r=_fith_dup(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		c->in_case=1;
		return r;
	}
	*/                               // end of re2c block
	break;
	case 4: // 5 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"clear" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_clear(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"sleep" {
		STACK_CHECK_DOWN_R(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_sleep(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	//~ "array" {
		//~ STACK_CHECK_DOWN_R(-1)
		//~ return _fith_array(c,r);
	//~ }
	"reads" { // (0fd, 1pBuf, TOS=sizeof(pBuf))
		STACK_CHECK_DOWN_R(-3)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_reads(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"leave" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"break;");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"again" {
		//~ *YYCURSORout = (c->cstk-2)->s;
		return r;
	}
	"strdup" { // might move to a library
		STACK_CHECK_DOWN_R(-1)
		u8 *buff;
		u64 size;
		size = strlen((const char *)r.tos.s)+1;
		buff = malloc(size);
		memmove(buff, r.tos.s, size);
		r.tos.s = buff;
		return r;
	}
	"debug" {
		return r;
	}
	"loadf" { // load file into memory, null terminated
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_loadf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	*/                               // end of re2c block
	break;
	case 5: // 6 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"return" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"return r;");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		// leave scope
		//leave_scope();
		return r;
	}
	"malloc" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_malloc(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"random" {
		STACK_CHECK_UP_R(1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_random(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		return r;
	}
	"memcmp" {
		STACK_CHECK_DOWN_R(-3)		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_memcmp(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	"writes" { // (0fd, 1pBuf)
		STACK_CHECK_DOWN_R(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_writes(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	*/                               // end of re2c block
	break;
	case 6: // 7 letter words
	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL
									 //
	* { // not a predefined token
		c->is_customWord =1;
		return r;
	} //   default rule with its semantic action start =YYCURSOR;

	"realloc" {
		STACK_CHECK_DOWN_R(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_realloc(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		return r;
	}
	*/                               // end of re2c block
	break;
	
	default:
	c->is_customWord =1;
	return r;
	}
	
	//~ stack_up_print:
	//~ printf("stack overflow!!!\n"); return r;
	//~ stack_down_print:
	//~ printf("stack underflow!!!\n");return r;
	
}

static Registers lex(Context1 *c, Registers r, Context2 *c2) // YYCURSOR is defined as a function parameter
{                                    //
	u8 *YYMARKER;    // YYMARKER is defined as a local variable
	//const u8 * YYCTXMARKER; // YYCTXMARKER is defined as a local variable
	u8 *YYCURSOR;    // YYCURSOR is defined as a local variable
	u8 *start;
	u8 tc;
	
	YYCURSOR = c->source_code;

loop: // label for looping within the lexxer
	start = YYCURSOR;
	//printf("start of loop\n");
	//print_code((YYCURSOR-0), 5);
	//printf("Hello\n");

	/*!re2c                          // start of re2c block **/
	re2c:define:YYCTYPE = "u8";      //   configuration that defines YYCTYPE
	re2c:yyfill:enable  = 0;         //   configuration that turns off YYFILL

	* { 
		u8 *s=start;
		u8 *f=YYCURSOR;
		//printf("char is %d, length %d \n", *s, YYCURSOR-start);
		while (*s!='\n'){
			s--;
		}
		s++;
		while (*f!='\n'){
			f++;
		}
		s++;
		printf("lex failure ");
		for (u32 ss=0; ss <(f-s); ss++){
			if(s[ss]==0){
				printf("\nnull in string!!!\n");
			} else{
			fputc ( s[ss], stdout);}
		}
		printf("\n");
		goto loop; 
	} //   default rule with its semantic action start =YYCURSOR;
	[\x03] { return r; }             // EOF rule with 0x03 sentinal
	
	[\x04] { // inside case statement, end of if
		// restore normal ending
		*(YYCURSOR-1)='}';
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"break;}}r=_fith_push(c,r,_fith_tmp);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		c->in_case=1;
		goto loop;
	}            
	
	wsp {
		while (start!=YYCURSOR){
			if(*start=='\n'){
				c->line_num+=1;
				
				if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
						<(128*1024*c->multiple[c->output_context]-64)){
					c->buffers[c->output_context]+=
						sprintf((char *)c->buffers[c->output_context],
							"\n");
				} else {
					if(expand_buffer(c)==0)
					{
						return r;
					}
				}
				
				//printf("wsp, %d\n", *line_num);
			}
			start++;
		}
		goto loop;
	}
 
	integer {
		STACK_CHECK_UP(1)
		
		c->last_constant = start;
		c->last_constant_len = (YYCURSOR-start);
		c->last_constant_type=0;
		tc = *YYCURSOR;
		*YYCURSOR=0;
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_push_i(c,r,%s);",
					start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		*YYCURSOR=tc;
		goto loop;
	}
	
	flt {
		STACK_CHECK_UP(1)
		
		c->last_constant = start;
		c->last_constant_len = (YYCURSOR-start);
		c->last_constant_type=1;
		
		tc = *YYCURSOR;
		*YYCURSOR=0;
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_push_d(c,r,%s);",
					start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		c->stack_index++;
		*YYCURSOR=tc;
		
		goto loop;
	}
	
	string_lit { 
		start++;
		u8 *string_start = start;
		c->last_constant = string_start;
		c->last_constant_type=2;
		// concatenate all multiline strings
		if(lex_string_lit_chain(&start))
		{
			// start is final null of created mangled_string_lit
			c->last_constant_len = (start-string_start);
			start++;
			// fill in with spaces until end
			while (start!=YYCURSOR){*start=' ';start++;}
		} else {
			c->last_constant_len = (YYCURSOR-1-string_start);
		}
		STACK_CHECK_UP(1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_push_s(c,r,(u8*)\"%s\");",
					string_start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	mangled_string_lit {
		STACK_CHECK_UP(1)
		start++;
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"s%d.s=(u8*)\"%s\";",
					c->stack_index,start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	char_lit {
		STACK_CHECK_UP(1)
		*(YYCURSOR-1)=0;
		start++;
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_push_i(c,r,(s64)'%s');",start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		c->last_constant = start;
		c->last_constant_len = (YYCURSOR-1-start);
		//~ sprintf((char *)c->buff, "r=_fith_push_i(c,r,'%c');",*start);
		//~ fwrite(c->buff,
		//~ sizeof(char),
		//~ strlen((const char *)c->buff),
		//~ c->outputFile[c->output_context]);
		
		goto loop;
	}

	";" { // end of function default return
		// pop command stack
		//~ c->cstk--;
		//~ // goto to return address
		//~ YYCURSOR = (u8 *)(((u64)c->cstk->s)&0x7FFFFFFFFFFFFFFF);
		// leave scope
		leave_scope();
		
		
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"return r;}\n");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		if(c->wbs_index>0){
			c->wbs_index--;
		}
		if(c->wbs_index==0){
			u8 *src = c->buffers_start[1];
			while(*src!='{'){src++;}src++;
			fwrite(c->buffers_start[1],
				sizeof(char),
				src-c->buffers_start[1],
				c->outputFile[1]);
			fwrite(c->buffers_start[2],
				sizeof(char),
				c->buffers[2]-c->buffers_start[2],
				c->outputFile[1]);
			fwrite(src,
				sizeof(char),
				c->buffers[1]-src,
				c->outputFile[1]);
			c->buffers[2]=c->buffers_start[2];
			c->buffers[1]=c->buffers_start[1];
			c->output_context=0;
		} else {
			u8 *src = c->word_buff_stack[c->wbs_index];
			while(*src!='{'){src++;}src++;
			fwrite(c->word_buff_stack[c->wbs_index],
				sizeof(char),
				src-c->word_buff_stack[c->wbs_index],
				c->outputFile[1]);
			fwrite(c->local_var_stack[c->wbs_index],
				sizeof(char),
				c->buffers[2]-c->local_var_stack[c->wbs_index],
				c->outputFile[1]);
			fwrite(src,
				sizeof(char),
				c->buffers[1]-src,
				c->outputFile[1]);
			c->buffers[2]=c->local_var_stack[c->wbs_index];
			c->buffers[1]=c->word_buff_stack[c->wbs_index];
		}
		
		
		
		
		//~ fwrite("return r;",
		//~ sizeof(char),
		//~ strlen("return r;"),
		//~ c->outputFile[c->output_context]);
		
		goto loop;
	}
	
	"}" {
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"}}");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		goto loop;
	}
	
	":" { // super complex
		STACK_CHECK_UP(1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
					sprintf((char *)c->buffers[c->output_context],
						"r=_fith_push_i(c,r,(s64)&_anon_func%d);", c->anon_func_count);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		c->output_context=1;
		c->local_var_stack[c->wbs_index] = c->buffers[2];
		c->word_buff_stack[c->wbs_index]=c->buffers[c->output_context];
		c->wbs_index++;
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
					sprintf((char *)c->buffers[c->output_context],
						"static Registers _anon_func%d(Context1 *c, Registers r){", c->anon_func_count);
			c->anon_func_count++;
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		enter_scope();
		//r = _fith_push_s(c, r, YYCURSOR);
		//YYCURSOR-=lex_if_else(&YYCURSOR, 2, 0); // skip definition
		goto loop;
	}

	"&" {
		STACK_CHECK_DOWN(-2)
		r=_fith_bitwise_and(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_bitwise_and(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"^" {
		STACK_CHECK_DOWN(-2)
		r=bitwise_xor(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=bitwise_xor(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"|" {
		STACK_CHECK_DOWN(-2)
		r=_fith_bitwise_or(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_bitwise_or(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"==" {
		STACK_CHECK_DOWN(-2)
		r=_fith_equals(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_equals(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"!=" {
		STACK_CHECK_DOWN(-2)
		r=_fith_not_equals(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_not_equals(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"<" {
		STACK_CHECK_DOWN(-2)
		r=_fith_less_than(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_less_than(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	">" {
		STACK_CHECK_DOWN(-2)
		r=_fith_greater_than(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_greater_than(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"<=" {
		STACK_CHECK_DOWN(-2)
		r=_fith_less_than_or_equals(c,r);
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_less_than_or_equals(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	">=" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_greater_than_or_equals(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"<<" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_shift_left(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	">>" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_shift_right(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"+" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_add(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"-" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_sub(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"/" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_divi(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	"*" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_mul(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"+f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_addf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"-f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_subf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"/f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_divif(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	"*f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_mulf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	"==f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_equalsf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"!=f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_not_equalsf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"<f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_less_thanf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	">f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_greater_thanf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"<=f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_less_than_or_equalsf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	">=f" {
		STACK_CHECK_DOWN(-2)
		
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_greater_than_or_equalsf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"%f" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_modulof(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"%" {
		STACK_CHECK_DOWN(-2)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_modulo(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"." {
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_print_stack(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	".f" {
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_print_stackf(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}
	
	"~" {
		STACK_CHECK_DOWN(-1)
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_bitwise_not(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		
		goto loop;
	}

	"=" { // assignment
		c->word_flags = 1;
		goto loop;
	}

	"=:" { // assignment of constant
		c->word_flags = 3;
		goto loop;
	}

	"+=" { // assignment
		c->word_flags = 4;
		goto loop;
	}
	
	"-=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x10;
		goto loop;
	}

	"*=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x20;
		goto loop;
	}

	"/=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x30;
		goto loop;
	}

	"%=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x40;
		goto loop;
	}

	"&=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x50;
		goto loop;
	}

	"|=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x60;
		goto loop;
	}

	"^=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x70;
		goto loop;
	}

	">>=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x80;
		goto loop;
	}

	"<<=" { // assignment
		c->word_flags = 4;
		c->word_flags |= 0x90;
		goto loop;
	}

	"@" {
		c->word_flags = 2;
		goto loop;
	}
	
	"[]" {
		STACK_CHECK_DOWN(-2)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_array_get(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		goto loop;
	}

	"=[]" {
		STACK_CHECK_DOWN(-3)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_array_set(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		goto loop;
	}

	"[];" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_array(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		goto loop;
	}

	"[].len" {
		STACK_CHECK_DOWN_R(-1)
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"r=_fith_array_len(c,r);");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		goto loop;
	}

	// new work flow. Check locals if any. Check functions. Check globals. Nothing found.
	word {
		//get_function_addr
		s64 *varP, tmp, val;
		u8 *ptr;
		s32 res;
		u8 flags;
		c->source_code = start;
		r = lex_word(c, r, &YYCURSOR, (YYCURSOR - start));
		if ( c->is_customWord ){
			switch(c->word_flags&0x0F){
				case 0: // no flags
				// check locals
				if(scope_index>0&&(vars[scope_index]!=0)){
					res = get_variable(start, (YYCURSOR - start), &val, scope_index);
					if (res!=0){
						STACK_CHECK_UP(1)
						tc = *YYCURSOR;
						*YYCURSOR=0;
						
						if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
								<(128*1024*c->multiple[c->output_context]-64)){
							c->buffers[c->output_context]+=
								sprintf((char *)c->buffers[c->output_context],
									"r=_fith_push(c,r,");
							*c->buffers[c->output_context] = *start;
							c->buffers[c->output_context]++;
							start++;
							while(*start!=0){
								if(isC_char(*start)){
									*c->buffers[c->output_context] = *start;
									c->buffers[c->output_context]++;
									start++;
								} else {
									*c->buffers[c->output_context] = '$';
									c->buffers[c->output_context]++;
									c->buffers[c->output_context]+=
									base64conversion(c->buffers[c->output_context], (*start-30));
									start++;
								}
							}
							
							c->buffers[c->output_context]+=
								sprintf((char *)c->buffers[c->output_context],
									");");
						} else {
							if(expand_buffer(c)==0)
							{
								return r;
							}
						}
						
						*YYCURSOR=tc;
						goto loop;
					}
				}
				// else
				// check if its a function
				ptr = (u8 *)get_function_addr(start, (YYCURSOR - start));
				if (ptr!=0){
					// IT IS A FUNCTION!!!
					tc = *YYCURSOR;
					*YYCURSOR=0;
					
					if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
							<(128*1024*c->multiple[c->output_context]-64)){
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								"r=");
						*c->buffers[c->output_context] = *start;
						c->buffers[c->output_context]++;
						start++;
						while(*start!=0){
							if(isC_char(*start)){
								*c->buffers[c->output_context] = *start;
								c->buffers[c->output_context]++;
								start++;
							} else {
								*c->buffers[c->output_context] = '$';
								c->buffers[c->output_context]++;
								c->buffers[c->output_context]+=
								base64conversion(c->buffers[c->output_context], (*start-30));
								start++;
							}
						}
						
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								"(c,r);");
					} else {
						if(expand_buffer(c)==0)
						{
							return r;
						}
					}
					
					*YYCURSOR=tc;
					//enter_scope();
					goto loop;
				}
				// else
				// check if its a global
				res = get_variable(start, (YYCURSOR - start), &val, 0);
				if (res!=0){
					STACK_CHECK_UP(1)
					tc = *YYCURSOR;
					*YYCURSOR=0;
					
					if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
							<(128*1024*c->multiple[c->output_context]-64)){
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								"r=_fith_push(c,r,");
						*c->buffers[c->output_context] = *start;
						c->buffers[c->output_context]++;
						start++;
						while(*start!=0){
							if(isC_char(*start)){
								*c->buffers[c->output_context] = *start;
								c->buffers[c->output_context]++;
								start++;
							} else {
								*c->buffers[c->output_context] = '$';
								c->buffers[c->output_context]++;
								c->buffers[c->output_context]+=
								base64conversion(c->buffers[c->output_context], (*start-30));
								start++;
							}
						}
						
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								");");
					} else {
						if(expand_buffer(c)==0)
						{
							return r;
						}
					}
					
					*YYCURSOR=tc;
					goto loop;
				}
				// nothing
				printf("Cannot find identifier as a local/function/global name!!!");
				print_code(start, (YYCURSOR - start));
				printf("\n");
				break;
				case 1: // assignment
				c->word_flags=0;
				STACK_CHECK_DOWN(-1)
				//r.sp--;
				// will try to insert unique name, if fails will update value only
				save_variable(start, (YYCURSOR - start), r.tos.i, 0, c);
				//r.tos.i = r.sp->i;
				break;
				case 2: // get address
				c->word_flags=0;
				// check locals
				if(scope_index>0&&(vars[scope_index]!=0)){
					ptr = (u8 *)get_variable_addr(start, (YYCURSOR - start), scope_index, &tmp);
					if (ptr!=0){
						STACK_CHECK_UP(1)
						tc = *YYCURSOR;
						*YYCURSOR=0;
						
						if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
								<(128*1024*c->multiple[c->output_context]-64)){
							c->buffers[c->output_context]+=
								sprintf((char *)c->buffers[c->output_context],
									"r=_fith_push_i(c,r,(s64)&");
							*c->buffers[c->output_context] = *start;
							c->buffers[c->output_context]++;
							start++;
							while(*start!=0){
								if(isC_char(*start)){
									*c->buffers[c->output_context] = *start;
									c->buffers[c->output_context]++;
									start++;
								} else {
									*c->buffers[c->output_context] = '$';
									c->buffers[c->output_context]++;
									c->buffers[c->output_context]+=
									base64conversion(c->buffers[c->output_context], (*start-30));
									start++;
								}
							}
							
							c->buffers[c->output_context]+=
								sprintf((char *)c->buffers[c->output_context],
									");");
						} else {
							if(expand_buffer(c)==0)
							{
								return r;
							}
						}
						
						*YYCURSOR=tc;
						goto loop;
					}
				}
				// else
				// check if its a function
				ptr = (u8 *)get_function_addr(start, (YYCURSOR - start));
				if (ptr!=0){
					STACK_CHECK_UP(1)
					tc = *YYCURSOR;
					*YYCURSOR=0;
					
					if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
							<(128*1024*c->multiple[c->output_context]-64)){
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								"r=_fith_push_i(c,r,(s64)&");
						*c->buffers[c->output_context] = *start;
						c->buffers[c->output_context]++;
						start++;
						while(*start!=0){
							if(isC_char(*start)){
								*c->buffers[c->output_context] = *start;
								c->buffers[c->output_context]++;
								start++;
							} else {
								*c->buffers[c->output_context] = '$';
								c->buffers[c->output_context]++;
								c->buffers[c->output_context]+=
								base64conversion(c->buffers[c->output_context], (*start-30));
								start++;
							}
						}
						
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								");");
					} else {
						if(expand_buffer(c)==0)
						{
							return r;
						}
					}
					
					*YYCURSOR=tc;
					goto loop;
				}
				// else
				// check if its a global
				ptr = (u8 *)get_variable_addr(start, (YYCURSOR - start), 0, &tmp);
				if (ptr!=0){
					STACK_CHECK_UP(1)
					tc = *YYCURSOR;
					*YYCURSOR=0;
					
					if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
							<(128*1024*c->multiple[c->output_context]-64)){
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								"r=_fith_push_i(c,r,(s64)&");
						*c->buffers[c->output_context] = *start;
						c->buffers[c->output_context]++;
						start++;
						while(*start!=0){
							if(isC_char(*start)){
								*c->buffers[c->output_context] = *start;
								c->buffers[c->output_context]++;
								start++;
							} else {
								*c->buffers[c->output_context] = '$';
								c->buffers[c->output_context]++;
								c->buffers[c->output_context]+=
								base64conversion(c->buffers[c->output_context], (*start-30));
								start++;
							}
						}
						
						c->buffers[c->output_context]+=
							sprintf((char *)c->buffers[c->output_context],
								");");
					} else {
						if(expand_buffer(c)==0)
						{
							return r;
						}
					}
					
					*YYCURSOR=tc;
					goto loop;
				}
				// nothing
				printf("Cannot find identifier as a local/function/global name!!!");
				print_code(start, (YYCURSOR - start));
				printf("\n");
				break;
				case 3: // assignment of constant
				c->word_flags=0;
				STACK_CHECK_DOWN(-1)
				//r.sp--;
				// will try to insert unique name, if fails will update value only
				save_variable(start, (YYCURSOR - start), r.tos.i, ((u64)0x80)<<56, c);
				//.tos.i = r.sp->i;
				break;
				case 4: // plus _fith_equals operator
				flags=c->word_flags;
				c->word_flags=0;
				STACK_CHECK_DOWN(-1)
				//~ r.sp--;
				//~ val = r.tos.i;
				//~ r.tos.i = r.sp->i;
				varP=0;
				// check locals
				if(scope_index>0&&(vars[scope_index]!=0)){
					varP = get_variable_addr(start, (YYCURSOR - start), scope_index, &tmp);
				}
				// else
				// check if its a global
				if(varP==0){
					varP = get_variable_addr(start, (YYCURSOR - start), 0, &tmp);
				}
				// nothing
				if (varP==0){
					printf("Cannot find identifier as a local/global name!!!");
					print_code(start, (YYCURSOR - start));
					printf("\n");
					goto loop;
				}
				// constant
				if((tmp&0x8000000000000000)!=0){
					printf("Cannot change constant: ");
					print_code(start, (YYCURSOR - start));
					printf("\n");
					goto loop;
				}
				// else
				// load -> modify -> store
				//~ tmp = *varP; // load
				
				tc = *YYCURSOR;
				*YYCURSOR=0;
				if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
						<(128*1024*c->multiple[c->output_context]-64)){
					*c->buffers[c->output_context] = *start;
					c->buffers[c->output_context]++;
					u8 *start_local = start+1;
					while(*start_local!=0){
						if(isC_char(*start_local)){
							*c->buffers[c->output_context] = *start_local;
							c->buffers[c->output_context]++;
							start_local++;
						} else {
							*c->buffers[c->output_context] = '$';
							c->buffers[c->output_context]++;
							c->buffers[c->output_context]+=
							base64conversion(c->buffers[c->output_context], (*start_local-30));
							start_local++;
						}
					}
					*c->buffers[c->output_context] = '.';
					c->buffers[c->output_context]++;
					*c->buffers[c->output_context] = 'i';
					c->buffers[c->output_context]++;
					
				} else {
					if(expand_buffer(c)==0)
					{
						return r;
					}
				}
				*YYCURSOR=tc;
				
				
				// modify
				switch(flags>>4){
					case 0:
					*c->buffers[c->output_context] = '+';
					c->buffers[c->output_context]++;
					break;
					case 1:
					*c->buffers[c->output_context] = '-';
					c->buffers[c->output_context]++;
					break;
					case 2:
					*c->buffers[c->output_context] = '*';
					c->buffers[c->output_context]++;
					break;
					case 3:
					*c->buffers[c->output_context] = '/';
					c->buffers[c->output_context]++;
					break;
					case 4:
					*c->buffers[c->output_context] = '%';
					c->buffers[c->output_context]++;
					break;
					case 5:
					*c->buffers[c->output_context] = '&';
					c->buffers[c->output_context]++;
					break;
					case 6:
					*c->buffers[c->output_context] = '|';
					c->buffers[c->output_context]++;
					break;
					case 7:
					*c->buffers[c->output_context] = '^';
					c->buffers[c->output_context]++;
					break;
					case 8:
					*c->buffers[c->output_context] = '>';
					c->buffers[c->output_context]++;
					*c->buffers[c->output_context] = '>';
					c->buffers[c->output_context]++;
					break;
					case 9:
					*c->buffers[c->output_context] = '<';
					c->buffers[c->output_context]++;
					*c->buffers[c->output_context] = '<';
					c->buffers[c->output_context]++;
					break;
				}
				
				c->buffers[c->output_context]+=
					sprintf((char *)c->buffers[c->output_context],
						"=r.tos.i;r=_fith_drop(c,r);");
				// store
				//~ *varP = tmp;
				break;
			}
		}
		goto loop;
	}
	
	function_definition {
		save_function_addr(start, (YYCURSOR - start-1), YYCURSOR);
		c->output_context=1;
		tc = *(YYCURSOR-1);
		*(YYCURSOR-1)=0;
		
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			if(*start<'a'){
				c->buffers[c->output_context]+=
					sprintf((char *)c->buffers[c->output_context],
						"Registers ");
				// TODO record public function
			} else {
				c->buffers[c->output_context]+=
					sprintf((char *)c->buffers[c->output_context],
						"static Registers ");
			}
			*c->buffers[c->output_context] = *start;
			c->buffers[c->output_context]++;
			start++;
			while(*start!=0){
				if(isC_char(*start)){
					*c->buffers[c->output_context] = *start;
					c->buffers[c->output_context]++;
					start++;
				} else {
					*c->buffers[c->output_context] = '$';
					c->buffers[c->output_context]++;
					c->buffers[c->output_context]+=
					base64conversion(c->buffers[c->output_context], (*start-30));
					start++;
				}
			}
			
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"(Context1 *c, Registers r){");
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		enter_scope();
		*(YYCURSOR-1)=tc;
		
		
		//YYCURSOR-=lex_if_else(&YYCURSOR, 2, 0); // skip definition
		goto loop;
	}
	
	goto_jump {
		tc = *(YYCURSOR-2);
		*(YYCURSOR-2)=0;
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"goto %s;", start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		*(YYCURSOR-2)=tc;
		
		goto loop;
	}
	
	goto_label {
		tc = *(YYCURSOR-2);
		*(YYCURSOR-2)=0;
		if((c->buffers[c->output_context]-c->buffers_start[c->output_context])
				<(128*1024*c->multiple[c->output_context]-64)){
			c->buffers[c->output_context]+=
				sprintf((char *)c->buffers[c->output_context],
					"%s:", start);
		} else {
			if(expand_buffer(c)==0)
			{
				return r;
			}
		}
		*(YYCURSOR-2)=tc;
		
		goto loop;
	}
	*/                               // end of re2c block
}



