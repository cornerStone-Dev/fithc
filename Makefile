
all: bin tool_output c_src bin/fith fith_src

bin/fith: src/fith_compiler.c src/fith_data.c src/fith_avl.c src/fith_words.c tool_output/fith_lex.c
	gcc -Os -march=native -fno-builtin-strlen -fno-stack-protector -s -o bin/fith src/fith_compiler.c -Wall
	size bin/fith

tool_output/fith_lex.c: src/fith_lex.re
	re2c -W --eager-skip src/fith_lex.re -o tool_output/fith_lex.c

bin:
	mkdir bin

tool_output:
	mkdir tool_output

c_src:
	mkdir c_src

fith_src:
	mkdir fith_src

clean:
	rm -f bin/flct
	rm -f tool_output/fith_gram.c
	rm -f tool_output/fith_lex.c
