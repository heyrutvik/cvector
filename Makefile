#gcc -c -Wall -Werror -fpic cvector.c
#gcc -shared -o libcvector.so cvector.o

CC=gcc
FPIC=-c -Wall -Werror -fpic
SO=-shared

all: cvector.o
	$(CC) $(SO) cvector.o -o libcvector.so

cvector.o:	cvector.c cvector.h
	$(CC) $(FPIC) cvector.c

clean:
	rm -rf cvector.o libcvector.so
