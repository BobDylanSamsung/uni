CC = gcc
CFLAGS = -Wall -Werror
target = fib

all: $(target)


$(target):$(target).c
	$(CC) $(CFLAGS) -o $(target) $(target).c -lm

clean: 
	rm $(target)

run:
	./$(target)
