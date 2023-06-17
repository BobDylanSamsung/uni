CC = gcc
CFLAGS = -Wall -Werror
target = argcomp

all: $(target)


$(target):$(target).c
	$(CC) $(CFLAGS) -o $(target) $(target).c -lm

clean: 
	rm $(target)

run:
	./$(target)
