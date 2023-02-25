CC = gcc
CFLAGS = -Wall -Werror -Wvla -O0 -std=c11 -g -fsanitize=address,leak

E2EDIR = tests/E2E

LIBS := -I${LIBDIR} #-lm

#TRADERS = $(wildcard $(TRADERDIR)/*.c)

TARGET = spx_exchange spx_trader

E2ETESTS := $(wildcard $(E2EDIR)/*)
E2ETESTFILES := $(patsubst $(E2EDIR)/%, $(E2EDIR)/%/*.c, $(E2ETESTS))
E2EEXECUTABLES := $(patsubst %.c, %, $(wildcard $(E2ETESTFILES)))

TESTCODE := $(wildcard $(E2EDIR)/*.c)
TESTBYTE := $(patsubst $(E2EDIR)/*/%.c, $(E2EDIR)/%, $(TESTCODE))

all: $(TARGET) $(E2EEXECUTABLES) tests/unit-tests
# 	@echo $(E2ETESTS)
# 	@echo ""
# 	@echo $(E2ETESTFILES)
# 	@echo ""
# 	@echo $(TEMP)
tests: $(E2ETESTFILES)

exchange: $(TARGET)

spx_exchange : spx_exchange.c
	${CC} ${CFLAGS} -o spx_exchange spx_exchange.c

spx_trader : spx_trader.c
	${CC} ${CFLAGS} -o spx_trader spx_trader.c

# $(E2EDIR)/% : $(E2EDIR)/%/test.c
# 	echo $@
# 	${CC} ${CFLAGS} -o $@/$< $@/$<.c

tests/unit-tests: tests/unit-tests.c
	${CC} ${CFLAGS} tests/unit-tests.c spx_exchange.c tests/libcmocka-static.a -DTESTING -o tests/unit-tests


$(E2EDIR)/% : $(E2EDIR)/%.c
	${CC} ${CFLAGS} -o $@ $<



git:
	git add *.c *.h
	git add Makefile
	git add tests/*
	git commit -m "submission"
	git push

kill:
	pkill --signal 9 trader
	#pkill --signal 9 spx



.PHONY: clean tests $(E2EDIR)/%

clean: 
	rm spx_trader
	rm spx_exchange
	rm $(E2EEXECUTABLES)
	rm tests/unit-tests
	rm /tmp/spx_*





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






