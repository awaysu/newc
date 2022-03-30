The program create basic c code, let you write code by myself right away.

# newc -h
newc version 1.0, author : awaysu@gmail.com
usage : newc [-p | -l] [project name]
p : program
l : libtest

# newc -p test1
# cd test1/
# ls
Makefile  main.c
# make
# ls
Makefile  hello.out  main.c
# ./hello.out
Hello World!

#
# newc -l test2
# cd test2/
# ls
Makefile  libtest.c  libtest.h  main.c
# make
# export export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
# ./hello.out
Hello World!




