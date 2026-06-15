CC = gcc
SRCS = main.c buffer.c Producer.c Consumer.c logger.c
TARGET = simulation

all:
	$(CC) -o $(TARGET) $(SRCS) -lpthread

clean:
	rm -f $(TARGET)