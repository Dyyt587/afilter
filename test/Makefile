CC = gcc
CFLAGS = -I. -I../src
UNITY = unity/unity.c
TARGET = unity_test

all: $(TARGET)

$(TARGET): $(UNITY) unity_test.c
	$(CC) $(CFLAGS) -o $(TARGET) $(UNITY) unity_test.c

clean:
	rm -f $(TARGET)