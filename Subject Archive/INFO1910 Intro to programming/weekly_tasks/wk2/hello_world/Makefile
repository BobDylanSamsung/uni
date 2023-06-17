CC = gcc
CFLAGS = -Wall -Werror -Wunreachable-code
TARGET = hello

# If the rule all is given then make the target
all: $(TARGET)

#If a particular target is given the make it
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

#If the clean is given then clean up the compiled files
clean:
	rm $(TARGET)

test:
	echo "test"
