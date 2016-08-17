CC = gcc
INCLUDE = ./
CFLAG = -Wall
SRC = main.c
EXEC_FILE = newc

make_api:$(SRC)
	$(CC) -o $(EXEC_FILE) $(CFLAG) -I$(INCLUDE) $(SRC)
clean:
	rm -f *.o $(EXEC_FILE)
