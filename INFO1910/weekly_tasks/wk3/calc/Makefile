CC = gcc
CFLAGS = -Wall
target = calc

all: $(target)


$(target):$(target).c
	$(CC) $(CFLAGS) -o $(target) $(target).c -lm

clean: 
	rm $(target)

run:
	./$(target)
