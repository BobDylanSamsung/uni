from src.variable_module import variable
from src.pointer_module import pointer
from src.printer_module import printer
from src.function_module import function
from src.function_module import function_converter
from src.loop_module import loop_converter

# class transpiler:
#     def __init__(self, c_file, py_file, printer):
#         self.c_file = c_file
#         self.py_file = py_file
#         self.printer = printer

#         self.terminators = [";", "{"]
#         self.paired_characters = { "(": ")", "'": "'", '"': '"', "[": "]"}


#         self.main_location = self.findmain(self.c_file)

#         self.keywords = ["#define", "#include"]

#         self.scope_open = 0
#         self.scope_close = 0

#     def findmain(self, c_file):     
#         found = False

#         while not found:
#             c_buf = c_file.read(9).decode("utf-8") #read 9 bytes and decode into string
#             if c_buf == "int main(": #check for declaration of main
#                 location = c_file.tell() #set location to begining of declaration
#                 print("location is %d" % (location))
#                 found = True
#             if not found:
#                 c_file.seek(-8, 1) #check starting from next byte

#         return(location)

#     def parse(self):
#         c_file = self.c_file
#         py_file = self.py_file

#         line = ''
#         word = ''
#         char = c_file.read(1)

#         while char:
#             word.append(char)
#             if word in self.keywords:


#             if char == ' ':
#                 line += word
#                 word = ''



#     def parse_main(self):
#         c_file = self.c_file
#         py_file = self.py_file
#         c_file.seek(self.main_location)
#         scope_open = 0
#         scope_close = 0

#         char = c_file.read(1).decode("utf-8")

#         if char != ')':
#             #command line arguments are present
#             py_file.write("import sys\n")
#             py_file.write("argc = len(sys.argv)\n")
#             py_file.write("argv = sys.argv\n")

#         while char != "{":
#         #do stuff
#             char = c_file.read(1).decode("utf-8")

#         scope_open += 1

#         word = ''
#         line = ''
#         expected = ''
#         pair_required = False

#         while scope_open != scope_close:
#             #body of main function
#             char = c_file.read(1).decode("utf-8")
#             print("char is %s\t\t" %char),
#             print(expected, char == expected)


#             if char not in self.terminators:
#                 #add character to word string
#                 word += char

#             # else:
#             #   if self.check_word(word):

#             if char in self.paired_characters:
#                 #stop checcking terminators
#                 pair_required = True
#                 expected = self.paired_characters[char]
#                 print("print expected is: ", expected)


#             elif str(char) == str(expected) and pair_required:
#                 #check terminators again
#                 print("\t\t\tshit fuck fuc")
#                 pair_required = False

#             if char in self.terminators and pair_required == False:
#                 if char == '{':
#                     scope_open += 1
#                     print("check scope\t open: %d\t close: %d" %(scope_open, scope_close))

#                 if char == '}':
#                     scope_close += 1
#                     print("check scope\t open: %d\t close: %d" %(scope_open, scope_close))

#                 if char == ';' or '\n':
#                     py_file.write(line)


#     def check_word(self, word):
#         if word in self.keywords:
#             return True
#         else:
#             return False

#     def printtest(self):
#         file = self.c_file
#         file.seek(location)
#         lines = file.readline()
#         cfile.write()


class basic_transpiler:
    def __init__(self, c_file, py_file):
        self.c_file = c_file
        self.py_file = py_file
        self.printer = printer(py_file)
        self.types = ["int", "char", "void", "float"]
        self.loops = ["for", "do", "while"]
        self.function_converter = function_converter()

    #will check if a character is valid in a variable/function name
    def check_char(self, char):
        acceptable = False

        if char.isalpha():
            acceptable = True

        if char.isdigit():
            acceptable = True

        if char == "_":
            acceptable = True

        return acceptable

    #checks for some sort of function in the line
    def find_func(self, line):
        words = line.split()
        string_to_write = line
        func_present = False
        for word in words:
            for i in range(len(word)-1):
                if self.check_char(word[i]) and word[i+1] == "(":
                    func_present = True
        return func_present

    def parse(self):
        self.printer.set_indent(0)
        self.printer.fprint("import sys")
        char = True
        line = ''
        word = ''
        loop = None
        paired_characters = {
        "'":"'", 
        '"':'"',
        "(":")"}
        pair_required = False
        required_character = ''
        while char:
            char = self.c_file.read(1).decode("utf-8")

            if not char:
                break

            # print(char,)
            if len(line) == 0:
                if char == "#":
                    # print("SKIPPING")
                    while char != '\n':
                        char = self.c_file.read(1).decode("utf-8")


            if char in paired_characters and pair_required == False:
                # print("RUN1")
                pair_required = True
                required_character = paired_characters[char]

            elif char == required_character:
                # print("RUN2")

                pair_required = False
                required_character = ''


            if not char.isspace():
                # print("RUN4")
                #add character to word
                word += char

            else:
                # print("RUN3")
                #add word to line

                if word in self.loops:
                    loop = word
                word += ' '
                line += word
                #print(char, '        ', word)
                word = ''

                if char == "\n" and len(line.lstrip()) == 0:
                    line = ''

            if pair_required == False:
                #add word to line
                if char == ";" or char == "{" or  char == "}":
                    line += word
                    word = ''
                    #end of line:
                    #find indent
                    self.printer.set_indent(self.find_indent(line))

                    #remove whitespace and newline
                    line = line.lstrip().strip()
                    if len(line) > 0:
                        string_to_write = self.parse_line(line, loop)
                        print("string to print is: ", string_to_write)
                        self.printer.fprint(string_to_write)
                        line = ''
                        word = ''
                        loop = None
        self.printer.set_indent(0)
        self.printer.fprint("main(len(sys.argv), sys.argv)")



    def parse_line(self, line, loop):
        line = line.lstrip()
        print("\t\t\t line is: {}\n\n\n".format(line))

        #check last character of the line
        if line[-1] == ";":    
            #definition
            pass
        elif line[-1] == "{":
            #loop or function
            pass

        #check for some sort of funciton in the line:

        func_present = self.find_func(line)
        print(func_present)

        #find what to do with line
        if line.lstrip()[-1] == "}" and len(line.lstrip()) == 1:
            string_to_write = ''
        elif loop != None:
            string_to_write = loop_converter(line, self.printer.get_indent()).convert(loop)

        elif line.split()[0] in self.types:
            #its a declaration
            #pass type
            pos = self.find_first_whitespace(line)
            #find name
            pos = self.find_first_char(line, pos)
            #check characters:
            i = 0
            func_dec = False
            while self.check_char(line[i + pos]):
                if line[i+pos+1] == "(":
                    #its a function
                    func_dec = True
                    func_name = line[pos:pos+i]
                i += 1


            if func_dec:
                if line[-1] == ";":
                    string_to_write = ''
                else:
                    string_to_write = function(line).declare()
                    self.function_converter.add_func(func_name)
                
            elif not func_dec:
                string_to_write = variable(line).declare(self.printer.get_indent())

        elif line.lstrip()[:6] == "return":
            print("\n\n\n")
            string_to_write = line[:line.find(";")]

        elif func_present:
            print("function is present")
            string_to_write = self.function_converter.convert(line)

        else:
            print("\n\n\n")
            string_to_write = line[:line.find(";")]        

        return string_to_write

    def find_indent(self, line):
        i = 0
        indent = 0
        while line[i:i+4] == "    ":
            indent += 1
            i += 4
        return indent


    def find_function(self, line):
        #possible functions
        declaration_keywords = ["int", "char", "float", "void"]

    def find_first_whitespace(self, line, start = 0):
        for i in range(start, len(line)):
            if line[i].isspace():
                return i 
        return(-1)

    def find_first_char(self, line, start = 0):
        for i in range(start, len(line)):
            if line[i].isalpha():
                return i
        return(-1)

    def altparse(self):
        lines = self.c_file.readlines()
        for i, line in enumerate(lines):
            print("\t\t Line Number is: {}\n \t\t Line is: {} \n\n\n".format(i, line))
            #find indent
            self.printer.set_indent(self.find_indent(line))

            #remove whitespace and newline
            line = line.lstrip().strip()
            if len(line) > 0:
                string_to_write = self.parse_line(line)
                print("string to print is: ", string_to_write)
                self.printer.fprint(string_to_write)