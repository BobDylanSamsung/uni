#!/bin/bash
touch novowels.txt
cd ~/../usr/share/dict
grep -v a words|grep -v e|grep -v i|grep -v o|grep -v u > /../../../home/wk1/novowels.txt
