submission for transpiler for assignment 2

items in directory:
    src: contains the source files required to transpile - all contain only modules used by transpiler.py
    test: my test cases. Running is automated through the Makefile. User input is not automated and output must be inspected for accuracy
    tests: provided test cases. No automated running
    Makefile: used to automate tests in test. See below for details
    transpiler.py: source file for the transpiler. See below for details for use



runnning a particular file:
    run transpiler.py
    will take 2 command line arguments
        1. the path to a c file to read from
        2. the path and name of a python file to transpile to
    order is irrelevant



running tests:
    running of tests in test directory is automated through the Makefile

    to run all tests use make command

    to run a particular set of tests in a subdirectory in test run make <subdirectory>

    test cases will be added to the "testcases" subdirectory in test - make clean will remove files in this directory and delete the directory

    assumed python version is python3 but this can be changed manually

    troubleshooting:
        make and make <subdirectory> will not work if test/testcases exists already - either remove manually or us make clean command

        make clean will not work if test/testcases exists but is empty. if this is the case remove it manually


transpiling multiple c files into one python file (linking):
    multiple c files can be transpiled into a single executable python file assuming only one main function is present by passing each file as a command line argument. order is irrelevant.