######################################
#c
######################################

CC = gcc
CFLAGS = -Wall
target = main

######################################
#Detect files and set paths accordingly
######################################

LIBDIR = lib
SRCDIR = src
BUILDDIR = build

LIBS := -I${LIBDIR} -lm

SRCFILES:= $(wildcard ${SRCDIR}/*.c)
OBJFILES:= $(patsubst ${SRCDIR}/%.c,${BUILDDIR}/%.o, ${SRCFILES})



all: ${target}


####################################
#build object files
####################################

${BUILDDIR}/%.o : ${SRCDIR}/%.c
	${CC} ${CFLAGS} ${LIBS} -c -o $@ $^ 


####################################
#Make executable file
####################################


${target} : ${BUILDDIR} ${OBJFILES} 
	${CC} ${CFLAGS} ${LIBS} -o $@ ${OBJFILES}

#####################################
#Make directories as needed
#####################################

${BUILDDIR}:
	mkdir ${BUILDDIR}






.PHONY: clean



clean: 
	rm -rf ${BUILDDIR}/*.o
	rmdir ${BUILDDIR}
	rm ${target}

run:
	./${target}