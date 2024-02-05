TARGET = task3

CC = gcc

clean:
	rm -rf *.o 

$(TARGET): $(TARGET).c func.c func.h
	$(CC) -O0 -g func.c $(TARGET).c -o $(TARGET)
	
val$(TARGET): $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
