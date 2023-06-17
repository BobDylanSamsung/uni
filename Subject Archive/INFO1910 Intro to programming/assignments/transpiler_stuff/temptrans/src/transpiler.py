import sys

#allocate files and set ppermissions. If True is passed then read bytes. By default bytes are not read
def allocate_files(read_bytes = False):
	for arg in sys.argv:
		if arg[-1] == 'c':
			c_file_path = arg
		if arg[-1] == 'y' and arg[-13:] != 'transpiler.py':
			py_file_path = arg

	c_file = open(c_file_path, "r" + "b"*read_bytes)
	py_file = open(py_file_path, "w" + "b"*read_bytes)	

	return (c_file, py_file)



def findmain(c_file):
	print("hello")
	
	found = False


	while not found:
		c_buf = c_file.read(9).decode("utf-8") #read 9 bytes and decode into string
		if c_buf == "int main(": #check for declaration of main
			location = c_file.tell() #set location to begining of declaration
			print("location is %d" % (location))
			found = True
		if not found:
			c_file.seek(-8, 1) #check starting from next byte

	return(location)


def trans_main(c_file, py_file, location):

	terminators = ["\n", ";", "{", "}"]
	paired_characters = { "(": ")", "'": "'", '"': '"', "[": "]"}

	c_file.seek(location)
	scope_open = 0
	scope_close = 0

	char = c_file.read(1)

	if char != ')':
		#command line arguments are present
		py_file.write("import sys\n")
		py_file.write("argc = len(sys.argv)\n")
		py_file.write("argv = sys.argv\n")

	while char != "{":
		#do stuff
		char = c_file.read(1)

	scope_open += 1

	line = ''
	expected = ''
	pair_required = False

	while scope_open != scope_close:
		#body of main function
		char = c_file.read(1)
		print("char is %s\t\t" %char),
		print(expected, char == expected)


		if char != terminators:
			#add character to word string
			line += char

		if char in paired_characters:
			#stop checcking terminators
			pair_required = True
			expected = paired_characters[char]
			print("print expected is: ", expected)


		elif str(char) == str(expected) and pair_required:
			#check terminators again
			print("\t\t\tshit fuck fuc")
			pair_required = False

		if char in terminators and pair_required == False:
			if char == '{':
				scope_open += 1
				print("check scope\t open: %d\t close: %d" %(scope_open, scope_close))

			if char == '}':
				scope_close += 1
				print("check scope\t open: %d\t close: %d" %(scope_open, scope_close))

			if char == ';' or '\n':
				parse_line(line, py_file)



def parse_line(line, py_file):
	print("line is %s" %line)










c_file, py_file = allocate_files(True)

location = findmain(c_file)

c_file, py_file = allocate_files()

trans_main(c_file, py_file, location)


c_file.close()
py_file.close()