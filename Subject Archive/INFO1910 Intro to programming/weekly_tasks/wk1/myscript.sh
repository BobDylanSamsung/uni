#!/bin/bash
#for i in seq 1 2 3 4 10;
#do
#    echo \$i
#done

for i in $(seq 1 10);
do
    echo $i
    if [ $(($i%2)) = 0 ];
    then
        echo even
    else
        echo odd
    fi
done

clear

foo = 0
while
