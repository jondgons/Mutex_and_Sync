#Name: Cody Gonsowski
#File: makefile
#Desc: makefile for assignment #3

CC=gcc

DEBUG=-g

TARGET=bank

CFLAGS=-c -Wall $(DEBUG)

all: $(TARGET)

$(TARGET): main.o 
	$(CC) -o $(TARGET) main.o -lpthread -no-pie

main.o: main.c
	$(CC) $(CFLAGS) main.c -no-pie

clean:
	rm *.o *~ $(TARGET)
