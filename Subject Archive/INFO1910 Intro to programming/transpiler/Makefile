TESTDIR = test
TEST_CASE_DIR := test/testcase

PYTHON := python3

PREPROCESSOR_TEST_DIR := ${TESTDIR}/preprocessor
FUNCTIONS_TEST_DIR := ${TESTDIR}/functions
COMMAND_LINE_TEST_DIR := ${TESTDIR}/command_line
VARIABLE_TEST_DIR := ${TESTDIR}/variables
INPUT_TEST_DIR := ${TESTDIR}/input
WHILE_TEST_DIR := ${TESTDIR}/while
FOR_TEST_DIR := ${TESTDIR}/for
IFELSE_TEST_DIR := ${TESTDIR}/ifelse
ARRAY_TEST_DIR := ${TESTDIR}/arrays
LINKER_TEST_DIR := ${TESTDIR}/linker

runtests: testdir preprocessor functions variables while for ifelse arrays linker command_line input
testdir:
	mkdir ${TEST_CASE_DIR}

preprocessor: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING PREPROCESSOR"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: guard_1"
	gcc -o ${TEST_CASE_DIR}/guard_1 ${PREPROCESSOR_TEST_DIR}/guard_1.c
	${PYTHON} transpiler.py ${PREPROCESSOR_TEST_DIR}/guard_1.c ${TEST_CASE_DIR}/guard_1.py	
	./${TEST_CASE_DIR}/guard_1
	${PYTHON} ${TEST_CASE_DIR}/guard_1.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: guard_2"
	gcc -o ${TEST_CASE_DIR}/guard_2 ${PREPROCESSOR_TEST_DIR}/guard_2.c
	${PYTHON} transpiler.py ${PREPROCESSOR_TEST_DIR}/guard_2.c ${TEST_CASE_DIR}/guard_2.py	
	./${TEST_CASE_DIR}/guard_2
	${PYTHON} ${TEST_CASE_DIR}/guard_2.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: guard_3"
	gcc -o ${TEST_CASE_DIR}/guard_3 ${PREPROCESSOR_TEST_DIR}/guard_3.c
	${PYTHON} transpiler.py ${PREPROCESSOR_TEST_DIR}/guard_3.c ${TEST_CASE_DIR}/guard_3.py	
	./${TEST_CASE_DIR}/guard_3
	${PYTHON} ${TEST_CASE_DIR}/guard_3.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: include_1"
	gcc -o ${TEST_CASE_DIR}/include_1 ${PREPROCESSOR_TEST_DIR}/include_1.c
	${PYTHON} transpiler.py ${PREPROCESSOR_TEST_DIR}/include_1.c ${TEST_CASE_DIR}/include_1.py	
	./${TEST_CASE_DIR}/include_1
	${PYTHON} ${TEST_CASE_DIR}/include_1.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: include_2"
	gcc -o ${TEST_CASE_DIR}/include_2 ${PREPROCESSOR_TEST_DIR}/include_2.c
	${PYTHON} transpiler.py ${PREPROCESSOR_TEST_DIR}/include_2.c ${TEST_CASE_DIR}/include_2.py	
	./${TEST_CASE_DIR}/include_2
	${PYTHON} ${TEST_CASE_DIR}/include_2.py
	@echo "done"

	@echo "\n\n\n"


functions: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING FUNCTIONS"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: add_1"
	gcc -o ${TEST_CASE_DIR}/add_1 ${FUNCTIONS_TEST_DIR}/add_1.c
	${PYTHON} transpiler.py ${FUNCTIONS_TEST_DIR}/add_1.c ${TEST_CASE_DIR}/add_1.py	
	./${TEST_CASE_DIR}/add_1
	${PYTHON} ${TEST_CASE_DIR}/add_1.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: add_2"
	gcc -o ${TEST_CASE_DIR}/add_2 ${FUNCTIONS_TEST_DIR}/add_2.c
	${PYTHON} transpiler.py ${FUNCTIONS_TEST_DIR}/add_2.c ${TEST_CASE_DIR}/add_2.py	
	./${TEST_CASE_DIR}/add_2
	${PYTHON} ${TEST_CASE_DIR}/add_2.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: linear"
	gcc -o ${TEST_CASE_DIR}/linear ${FUNCTIONS_TEST_DIR}/linear.c
	${PYTHON} transpiler.py ${FUNCTIONS_TEST_DIR}/linear.c ${TEST_CASE_DIR}/linear.py	
	./${TEST_CASE_DIR}/linear
	${PYTHON} ${TEST_CASE_DIR}/linear.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: quadratic"
	gcc -o ${TEST_CASE_DIR}/quadratic ${FUNCTIONS_TEST_DIR}/quadratic.c
	${PYTHON} transpiler.py ${FUNCTIONS_TEST_DIR}/quadratic.c ${TEST_CASE_DIR}/quadratic.py	
	./${TEST_CASE_DIR}/quadratic
	${PYTHON} ${TEST_CASE_DIR}/quadratic.py
	@echo "done"

command_line: testdir
	@echo "/////////////////////////////////"
	@echo "//command_line"
	@echo "/////////////////////////////////"
	@echo "\n"



	@echo "TESTCASE: command_1"
	gcc -o ${TEST_CASE_DIR}/command_1 ${COMMAND_LINE_TEST_DIR}/command_1.c
	${PYTHON} transpiler.py ${COMMAND_LINE_TEST_DIR}/command_1.c ${TEST_CASE_DIR}/command_1.py	
	./${TEST_CASE_DIR}/command_1 2 7
	${PYTHON} ${TEST_CASE_DIR}/command_1.py 2 7
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: command_2"
	gcc -o ${TEST_CASE_DIR}/command_2 ${COMMAND_LINE_TEST_DIR}/command_2.c
	${PYTHON} transpiler.py ${COMMAND_LINE_TEST_DIR}/command_2.c ${TEST_CASE_DIR}/command_2.py	
	./${TEST_CASE_DIR}/command_2 4 9
	${PYTHON} ${TEST_CASE_DIR}/command_2.py 4 9
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: command_3"
	gcc -o ${TEST_CASE_DIR}/command_3 ${COMMAND_LINE_TEST_DIR}/command_3.c
	${PYTHON} transpiler.py ${COMMAND_LINE_TEST_DIR}/command_3.c ${TEST_CASE_DIR}/command_3.py	
	./${TEST_CASE_DIR}/command_3 9
	${PYTHON} ${TEST_CASE_DIR}/command_3.py 9
	@echo "done"

variables: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING VARIBLES"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: integers"
	gcc -o ${TEST_CASE_DIR}/integers ${VARIABLE_TEST_DIR}/integers.c
	${PYTHON} transpiler.py ${VARIABLE_TEST_DIR}/integers.c ${TEST_CASE_DIR}/integers.py	
	./${TEST_CASE_DIR}/integers
	${PYTHON} ${TEST_CASE_DIR}/integers.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: characters"
	gcc -o ${TEST_CASE_DIR}/characters ${VARIABLE_TEST_DIR}/characters.c
	${PYTHON} transpiler.py ${VARIABLE_TEST_DIR}/characters.c ${TEST_CASE_DIR}/characters.py	
	./${TEST_CASE_DIR}/characters
	${PYTHON} ${TEST_CASE_DIR}/characters.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: float"
	gcc -o ${TEST_CASE_DIR}/float ${VARIABLE_TEST_DIR}/float.c
	${PYTHON} transpiler.py ${VARIABLE_TEST_DIR}/float.c ${TEST_CASE_DIR}/float.py	
	./${TEST_CASE_DIR}/float
	${PYTHON} ${TEST_CASE_DIR}/float.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: mixed"
	gcc -o ${TEST_CASE_DIR}/mixed ${VARIABLE_TEST_DIR}/mixed.c
	${PYTHON} transpiler.py ${VARIABLE_TEST_DIR}/mixed.c ${TEST_CASE_DIR}/mixed.py	
	./${TEST_CASE_DIR}/mixed
	${PYTHON} ${TEST_CASE_DIR}/mixed.py
	@echo "done"

input: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING INPUT"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: scanf_1"
	gcc -o ${TEST_CASE_DIR}/scanf_1 ${INPUT_TEST_DIR}/scanf_1.c
	${PYTHON} transpiler.py ${INPUT_TEST_DIR}/scanf_1.c ${TEST_CASE_DIR}/scanf_1.py	
	./${TEST_CASE_DIR}/scanf_1
	${PYTHON} ${TEST_CASE_DIR}/scanf_1.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: scanf_2"
	gcc -o ${TEST_CASE_DIR}/scanf_2 ${INPUT_TEST_DIR}/scanf_2.c
	${PYTHON} transpiler.py ${INPUT_TEST_DIR}/scanf_2.c ${TEST_CASE_DIR}/scanf_2.py	
	./${TEST_CASE_DIR}/scanf_2
	${PYTHON} ${TEST_CASE_DIR}/scanf_2.py
	@echo "done"	

while: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING WHILE"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: while_1"
	gcc -o ${TEST_CASE_DIR}/while_1 ${WHILE_TEST_DIR}/while_1.c
	${PYTHON} transpiler.py ${WHILE_TEST_DIR}/while_1.c ${TEST_CASE_DIR}/while_1.py	
	./${TEST_CASE_DIR}/while_1
	${PYTHON} ${TEST_CASE_DIR}/while_1.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: while_2"
	gcc -o ${TEST_CASE_DIR}/while_2 ${WHILE_TEST_DIR}/while_2.c
	${PYTHON} transpiler.py ${WHILE_TEST_DIR}/while_2.c ${TEST_CASE_DIR}/while_2.py	
	./${TEST_CASE_DIR}/while_2
	${PYTHON} ${TEST_CASE_DIR}/while_2.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: while_3"
	gcc -o ${TEST_CASE_DIR}/while_3 ${WHILE_TEST_DIR}/while_3.c
	${PYTHON} transpiler.py ${WHILE_TEST_DIR}/while_3.c ${TEST_CASE_DIR}/while_3.py	
	./${TEST_CASE_DIR}/while_3
	${PYTHON} ${TEST_CASE_DIR}/while_3.py
	@echo "done"


	@echo "\n\n\n"
	@echo "TESTCASE: while_4"
	gcc -o ${TEST_CASE_DIR}/while_4 ${WHILE_TEST_DIR}/while_4.c
	${PYTHON} transpiler.py ${WHILE_TEST_DIR}/while_4.c ${TEST_CASE_DIR}/while_4.py	
	./${TEST_CASE_DIR}/while_4
	${PYTHON} ${TEST_CASE_DIR}/while_4.py
	@echo "done"

for: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING FOR"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: for_1"
	gcc -o ${TEST_CASE_DIR}/for_1 ${FOR_TEST_DIR}/for_1.c
	${PYTHON} transpiler.py ${FOR_TEST_DIR}/for_1.c ${TEST_CASE_DIR}/for_1.py	
	./${TEST_CASE_DIR}/for_1
	${PYTHON} ${TEST_CASE_DIR}/for_1.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: for_2"
	gcc -o ${TEST_CASE_DIR}/for_2 ${FOR_TEST_DIR}/for_2.c
	${PYTHON} transpiler.py ${FOR_TEST_DIR}/for_2.c ${TEST_CASE_DIR}/for_2.py	
	./${TEST_CASE_DIR}/for_2
	${PYTHON} ${TEST_CASE_DIR}/for_2.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: for_3"
	gcc -o ${TEST_CASE_DIR}/for_3 ${FOR_TEST_DIR}/for_3.c
	${PYTHON} transpiler.py ${FOR_TEST_DIR}/for_3.c ${TEST_CASE_DIR}/for_3.py	
	./${TEST_CASE_DIR}/for_3
	${PYTHON} ${TEST_CASE_DIR}/for_3.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: for_4"
	gcc -o ${TEST_CASE_DIR}/for_4 ${FOR_TEST_DIR}/for_4.c
	${PYTHON} transpiler.py ${FOR_TEST_DIR}/for_4.c ${TEST_CASE_DIR}/for_4.py	
	./${TEST_CASE_DIR}/for_4
	${PYTHON} ${TEST_CASE_DIR}/for_4.py
	@echo "done"

ifelse: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING IFELSE"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: if_1"
	gcc -o ${TEST_CASE_DIR}/if_1 ${IFELSE_TEST_DIR}/if_1.c
	${PYTHON} transpiler.py ${IFELSE_TEST_DIR}/if_1.c ${TEST_CASE_DIR}/if_1.py	
	./${TEST_CASE_DIR}/if_1
	${PYTHON} ${TEST_CASE_DIR}/if_1.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: else_1"
	gcc -o ${TEST_CASE_DIR}/else_1 ${IFELSE_TEST_DIR}/else_1.c
	${PYTHON} transpiler.py ${IFELSE_TEST_DIR}/else_1.c ${TEST_CASE_DIR}/else_1.py	
	./${TEST_CASE_DIR}/else_1
	${PYTHON} ${TEST_CASE_DIR}/else_1.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: elif_1"
	gcc -o ${TEST_CASE_DIR}/elif_1 ${IFELSE_TEST_DIR}/elif_1.c
	${PYTHON} transpiler.py ${IFELSE_TEST_DIR}/elif_1.c ${TEST_CASE_DIR}/elif_1.py	
	./${TEST_CASE_DIR}/elif_1
	${PYTHON} ${TEST_CASE_DIR}/elif_1.py
	@echo "done"



arrays: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING ARRAYS"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: int_array"
	gcc -o ${TEST_CASE_DIR}/int_array ${ARRAY_TEST_DIR}/int_array.c
	${PYTHON} transpiler.py ${ARRAY_TEST_DIR}/int_array.c ${TEST_CASE_DIR}/int_array.py	
	./${TEST_CASE_DIR}/int_array
	${PYTHON} ${TEST_CASE_DIR}/int_array.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: float_array"
	gcc -o ${TEST_CASE_DIR}/float_array ${ARRAY_TEST_DIR}/float_array.c
	${PYTHON} transpiler.py ${ARRAY_TEST_DIR}/float_array.c ${TEST_CASE_DIR}/float_array.py	
	./${TEST_CASE_DIR}/float_array
	${PYTHON} ${TEST_CASE_DIR}/float_array.py
	@echo "done"


linker: testdir
	@echo "/////////////////////////////////"
	@echo "//TESTING LINKER"
	@echo "/////////////////////////////////"
	@echo "\n"

	@echo "TESTCASE: case_1"
	gcc -o ${TEST_CASE_DIR}/linker_1 ${LINKER_TEST_DIR}/case_1/main.c ${LINKER_TEST_DIR}/case_1/add_2.c ${LINKER_TEST_DIR}/case_1/print.c
	${PYTHON} transpiler.py ${TEST_CASE_DIR}/linker_1.py ${LINKER_TEST_DIR}/case_1/main.c ${LINKER_TEST_DIR}/case_1/add_2.c ${LINKER_TEST_DIR}/case_1/print.c
	./${TEST_CASE_DIR}/linker_1
	${PYTHON} ${TEST_CASE_DIR}/linker_1.py
	@echo "done"

	@echo "\n\n\n"
	@echo "TESTCASE: case_2"
	gcc -o ${TEST_CASE_DIR}/linker_2 ${LINKER_TEST_DIR}/case_2/main.c ${LINKER_TEST_DIR}/case_2/fib.c ${LINKER_TEST_DIR}/case_2/print.c
	${PYTHON} transpiler.py ${TEST_CASE_DIR}/linker_2.py ${LINKER_TEST_DIR}/case_2/main.c ${LINKER_TEST_DIR}/case_2/fib.c ${LINKER_TEST_DIR}/case_2/print.c
	./${TEST_CASE_DIR}/linker_2 15
	${PYTHON} ${TEST_CASE_DIR}/linker_2.py 15
	@echo "done"
clean:
	rm ${TEST_CASE_DIR}/*
	rmdir ${TEST_CASE_DIR}



