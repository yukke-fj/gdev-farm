# Makefile
TARGET	= user_test
CC	= gcc
NVCC	= nvcc -arch sm_20 -cubin
LIBS	= -lucuda -lgdev
CFLAGS	= -L /usr/local/gdev/lib64 -I /usr/local/gdev/include

all:
	gcc -o $(TARGET) $(CFLAGS) $(LIBS) main.c memcpy_pinned.c

clean:
	rm -f $(TARGET) *.cubin ./*~
