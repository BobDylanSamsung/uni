import sys

filename = "files/" + sys.argv[1] + ".txt"
output = "../vr2017/binary_files/" + sys.argv[1] + ".bin"
infile = open(filename, "r")
outfile = open(output, "wb")


for line in infile.readlines():
	for num in line.strip().split(" "):
		outfile.write(int(num).to_bytes(1, byteorder = 'big', signed = False))

infile.close()
outfile.close()
