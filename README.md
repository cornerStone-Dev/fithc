# fith

This project is a compiler for the fith programming language.

To build the project requires gcc, make, and re2c. If on Ubunutu intall build-essential and re2c.

Clone from git, then `$ make`

Browse the Makefile for more information on building.

Browse test.fith in fith_src/ for examples on usage. You can run it after making as:

`$ ./bin/fith fith_src/test.fith`

or for a short way to do the whole thing

`make && ./bin/fith fith_src/test.fith && gcc -O2 -march=native -fno-builtin-strlen -fno-stack-protector -s -o bin/output c_src/main.c -Wall && ./bin/output`
