import sys
from functools import reduce
from operator import xor

check = 0
for a in sys.argv[1:]:
	check ^= int(a)

print(check)