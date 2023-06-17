CC = gcc
Cflags = -Wall -Werror
Target = casttest

all: $(Target)

$(Target) : $(Target).c
	$(CC) $(Cflags) -o $(Target) $(Target).c

clean:
	rm $(Target)

run: $(Target)
	./$(Target)
