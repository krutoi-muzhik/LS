TARGET = ls
CC = gcc
CFLAGS = -c -Wall

$(TARGET): main.o ls.o
	$(CC) main.o ls.o -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(TARGET) *.o
