CC = gcc
CFLAGS = -Wall -Werror -Wvla -O0 -std=c11 -g -fsanitize=address,leak

BUILDDIR = build
SRCDIR = src
LIBDIR = lib

LIBS := -I${LIBDIR} -lm


SRCFILES:= $(wildcard ${SRCDIR}/*.c)
EXECFILES:= $(patsubst ${SRCDIR}/%.c,%, ${SRCFILES})


all: ${EXECFILES}



%: ${SRCDIR}/%.c
	${CC} ${CFLAGS} ${LIBS} -o $@ $^

clean: 
	#rm -r ${BUILDDIR}
	rm ${EXECFILES}







