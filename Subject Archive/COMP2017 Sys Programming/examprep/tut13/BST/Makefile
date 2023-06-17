CC = gcc
CFLAGS = -Wall -Werror -Wvla -O0 -std=c11 -g -fsanitize=address,leak

BUILDDIR = build
SRCDIR = src
LIBDIR = lib

LIBS := -I${LIBDIR} -lm

SRCFILES:= $(wildcard ${SRCDIR}/*.c)
OBJFILES:= $(patsubst ${SRCDIR}/%.c,${BUILDDIR}/%.o, ${SRCFILES})

TARGET = tree

all: ${TARGET}


${TARGET}: ${BUILDDIR} ${OBJFILES}
	${CC} ${CFLAGS} ${LIBS} -o $@ ${OBJFILES}

${BUILDDIR}:
	mkdir -p ${BUILDDIR}

${BUILDDIR}/%.o : ${SRCDIR}/%.c
	${CC} ${CFLAGS} ${LIBS} -c -o $@ $<

clean: 
	rm -r -f ${BUILDDIR}
	rm -f ${TARGET}




#all: target

# # ####################################
# # #build object files
# # ####################################

# ${BUILDDIR}/%.o: ${SRCDIR}/%.c
# 	${CC} ${CFLAGS} -c -o $@  $< ${LIBS} 


# # ####################################
# # #Make executable file
# # ####################################


# target : ${OBJFILES}
# 	${CC} ${CFLAGS} ${LIBS} -o $@ $^

# #####################################
# #Make directories as needed
# #####################################

# ${BUILDDIR}:
# 	mkdir ${BUILDDIR}






