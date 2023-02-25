#!/bin/bash

cd ~/../../usr/share/dict

#newlist=$(grep -v a words)
newlist="test"

for char in e i o u;
do
	cat $char
	sudo rm novowels
	sudo touch novowels
	#let $newlist=$(grep -v
	sudo bash -c 'echo $newlist > novowels'
	cat $novowels
	#let $newlist=$(grep -v $char novowels)
done


cat $newlist
