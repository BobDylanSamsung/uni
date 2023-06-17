#!/bin/bash


e2edir="./tests/E2E/"

if [ $# == 0 ]
then
	for TEST in $(find tests/E2E/* -maxdepth 0); do
	    echo ""
	    echo ""
	    echo ""
	    echo TESTING $TEST
	    echo ----------------------------------------------------------------------    
	    cat $TEST/run.sh
	    echo ""

		#diff $TEST/test.out <(./spx_exchange $TEST/products.txt $TEST/test) && echo "    SUCCESS!" || echo "    FAILURE."
		diff -Z -B $TEST/test.out <(bash $TEST/run.sh) && echo "SUCCESS!" || echo "FAILURE."
		#diff -u $TEST/test.out <(./spx_exchange $TEST/products.txt $TEST/test)
		sleep 1
		# pkill --signal 9 spx
		# pkill --signal 9 trader
		# rm /tmp/spx_*

	done
elif [ $1 == "unittest" ]
then
	./tests/unit-tests
else
	for TEST in $@; do
		echo ""
	    # echo ""
	    echo TESTING $e2edir$TEST
	    echo ----------------------------------------------------------------------    
	    cat $e2edir$TEST/run.sh
	    echo ""

		#diff $TEST/test.out <(./spx_exchange $TEST/products.txt $TEST/test) && echo "    SUCCESS!" || echo "    FAILURE."
		diff -Z -B -y $e2edir$TEST/test.out <(bash $e2edir$TEST/run.sh) && echo "SUCCESS!" || echo "FAILURE."
	done
fi 




	

#./spx_exchange $e2edir/basic_products.txt $e2edir/basic
