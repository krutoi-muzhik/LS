TARGET = ls
CC = gcc

$(TARGET): main.o ls.o
	$(CC) main.o ls.o -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm $(TARGET) *.o
