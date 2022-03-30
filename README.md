The program creates basic c code, letting you write code by yourself right away.
** **
**Help**
```
# newc -h
newc version 1.0, author : awaysu@gmail.com
usage : newc [-p | -l] [project name]
p : program
l : libtest
```
** **
**Create code for program**
```
# newc -p test1
# cd test1/
# ls
Makefile  main.c
# make
# ls
Makefile  hello.out  main.c
# ./hello.out
Hello World!
```
** **
**Create code for program & library**
```
# newc -l test2
# cd test2/
# ls
Makefile  libtest.c  libtest.h  main.c
# make
# export export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
# ./hello.out
Hello World!
```



