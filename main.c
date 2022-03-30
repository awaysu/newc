#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define APP_CCODE_FILE		"main.c"
#define LIB_HCODE_FILE		"libtest.h"
#define LIB_CCODE_FILE		"libtest.c"
#define MAKEFILE_FILE		"Makefile"

char *APP_CCODE=
{
	"#include \"stdio.h\"\n\nint main(int argc, char *argv[])\n{\n    printf(\"Hello World!\\n\");\n    return 0;\n}\n"
};

char *APP_MAKEFILE=
{
	"CC = gcc\nINCLUDE = ./\nCFLAG = -Wall\nSRC = main.c\nEXEC_FILE = hello.out\n\nmake_api:$(SRC)\n\t$(CC) -o $(EXEC_FILE) $(CFLAG) -I$(INCLUDE) $(SRC)\nclean:\n\trm -f *.o $(EXEC_FILE)\n"
};

char *LIB_HCODE=
{
	"extern void ShowHelloWorld();\nvoid ShowHelloWorld();"
};

char *LIB_CCODE=
{
	"#include \"libtest.h\"\n#include \"stdio.h\"\n\nvoid ShowHelloWorld()\n{\n    printf(\"Hello World!\\n\");\n}\n"
};

char *LIB2_CCODE=
{
	"#include \"libtest.h\"\n\nint main(int argc, char *argv[])\n{\n    ShowHelloWorld();\n    return 0;\n}\n"
};

char *LIB_MAKEFILE=
{
	"CC = gcc\nSRC = ./main.c\nINCLUDE = -I./\nCFLAG = -Wall -ltest -L./\nEXEC_FILE = ./hello.out\n\nLIB = ./libtest.c\nLIB_CFLAG = -Wall -fPIC -shared\nLIB_NAME = ./libtest.so\n\nall:make_lib make_api\n\nmake_api:$(SRC)\n\t$(CC) -o $(EXEC_FILE) $(CFLAG) $(INCLUDE) $(LIB_NAME) $(SRC)\n\nmake_lib:$(LIB)\n\t$(CC) -o $(LIB_NAME) $(LIB_CFLAG) $(LIB)\nclean:\n\trm -f *.so $(EXEC_FILE)\n"
};

int save_file(char *pFolder, char *pFile, char *pBuf, unsigned int length)
{
    int    fd = 0;
    int    retValue = -1;
	
	char path[0x64];
	
	memset(path, '\0', 0x64);
	sprintf(path, "%s/%s", pFolder, pFile);
	
    if ( (fd = open( path, 
    	      O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) > 0 )
    {
		if ( write(fd, pBuf, length) == length )
			retValue = 0;
		else		
			printf("%s write to file %s fail\n", __FUNCTION__, pFile );	
			
		if (fd)	close(fd);
		sync();			
	}
	else
        printf("%s create %s file fail\n", __FUNCTION__, pFile);
    
    return retValue;
}

void createFolder(char *f)
{
	struct stat st = {0};
	
	if (stat(f, &st) == -1) 
	{
		mkdir(f, 0700);
	}
}

void help()
{

	printf("newc version 1.0, author : awaysu@gmail.com\n");
	printf("usage : newc [-p | -l] [project name]\n");
    printf("p : program\n");
    printf("l : libtest\n");
	

}

int main(int argc, char *argv[])
{

	if (argv[1] && argv[2] )
	{
		if (strcmp(argv[1], "-p") == 0)
		{	
			createFolder(argv[2]);
			
			save_file(argv[2], APP_CCODE_FILE, APP_CCODE, strlen(APP_CCODE));
			save_file(argv[2], MAKEFILE_FILE, APP_MAKEFILE, strlen(APP_MAKEFILE));

		}
		else if (strcmp(argv[1], "-l") == 0)
		{
			createFolder(argv[2]);
			
			save_file(argv[2], LIB_HCODE_FILE, LIB_HCODE, strlen(LIB_HCODE));
			save_file(argv[2], LIB_CCODE_FILE, LIB_CCODE, strlen(LIB_CCODE));
			save_file(argv[2], APP_CCODE_FILE, LIB2_CCODE, strlen(LIB2_CCODE));
			save_file(argv[2], MAKEFILE_FILE, LIB_MAKEFILE, strlen(LIB_MAKEFILE));
		}
		else
			help();
	}
	else
		help();
		
		
    return 0;
}
