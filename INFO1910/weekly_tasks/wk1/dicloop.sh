#!/bin/bash
#cd ~/../../usr/share/dict
pwd

#make file and put contents of dictionary in file
novowels=word_list.txt

sudo bash -c "chmod 777 $novowels"

sudo bash -c "cat ~/../../usr/share/dict/words > $novowels"
a=1
for char in a e i o u;
do
	#remove the words with each vowel in them
	#store in temp variable then replace list with contents of variable	
	newlist=$(grep -v $char $novowels)
	for i in $newlist;
	do
		if [ $a == 1 ]
		then
			echo $i > $novowels
		else
			echo $i >> $novowels
		fi
		#cat $novowels
		a=0
	done
	
done


#echo $newlist

cat $novowels