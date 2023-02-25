CC = gcc
CFLAGS = -Wall
target = gotoloop

all: $(target)


$(target):$(target).c
	$(CC) $(CFLAGS) -o $(target) $(target).c $(target).h -lm

clean: 
	rm $(target)

run:
	./$(target)
