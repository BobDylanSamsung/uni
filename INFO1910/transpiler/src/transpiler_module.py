from src.variable_module import variable
from src.pointer_module import pointer
from src.function_module import function
from src.function_module import Function_Converter
from src.loop_module import loop_converter
from src.preprocessor_module import Preprocessor
from src.struct_module import Struct_Converter

#transpiler object which parses over the file - does the bulk of the work
class basic_transpiler:
    #initialise values
        #py_file: file to output to
        #printer: module to print to file
        #types: variable types
        #loops: loops that can be converted
        #function_converter: Function_Converter object
        #struct_converter: Struct_Converter object
    def __init__(self, py_file, printer):
        self.py_file = py_file
        self.printer = printer        
        self.types = ["int", "char", "void", "float", "long"]
        self.loops = ["for", "do", "while", "if"]
        self.function_converter = Function_Converter()      #define funciton converter module
        self.struct_converter = Struct_Converter()


    #set c_file
    #sets c_file to a filestream
    def set_c_file(self, filestream):
        self.c_file = filestream 
        self.preprocessor = Preprocessor(self.printer, self.py_file, self.c_file, self)       #define preprocessor module for a particular filestream


    #check_char
    #checks if a character is acceptable in a function name

    #character: character to check

    #returns boolean value indicating if its a valid character
    def check_char(self, char):
        acceptable = False

        if char.isalpha():
            acceptable = True

        if char.isdigit():
            acceptable = True

        if char == "_":
            acceptable = True

        return acceptable

    #find_func
    #checks for some sort of function in the line

    #line: line to search through

    #returns if function is present and the name of the function. name is empty if no function is found
    def find_func(self, line):
        words = line.split()
        string_to_write = line
        func_present = False
        func_name = None
        for word in words:
            for i in range(len(word)-1):
                if self.check_char(word[i]) and word[i+1] == "(":
                    func_present = True
                    func_name = word[:i+1]

        return func_present, func_name

    #parse
    #main module for parsing through a file

    #alt_file: alternative file that isnt the main for use in linking files

    #returns nothing
    def parse(self, alt_file = None):
        #set file
        if alt_file:
            c_file = alt_file
        else:
            c_file = self.c_file
        self.printer.set_indent(0)
        

        
        #initialise values used in parsing
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
        
        #loop through file character by character
        while char:
            char = c_file.read(1)


            if not char:
                break

            #passes line to preprocessor - if comment it is excluded by the preprocessor
            if len(line.lstrip()) == 0 and char == "#":
                while char != '\n' and char:
                    line += char
                    char = c_file.read(1)        
                guard = self.preprocessor.convert(line)

                #if guard is activated then skip until the end of the guard
                if guard:  
                    check = ''
                    for x in range(len("#endif")):
                        check += c_file.read(1)
                    while check != "#endif":
                        check = check[1:] + c_file.read(1)
                line = ''


            #check for a pair required to avoid passing in incomplete lines
            if char in paired_characters and pair_required == False:
                pair_required = True
                required_character = paired_characters[char]

            elif char == required_character:

                pair_required = False
                required_character = ''


            if not char.isspace():
                #add character to word
                word += char

            else:
                #add word to line
                if word in self.loops:
                    loop = word

                #convert tabs to 4 spaces
                if char == chr(9):
                    word += '    '            
                else:
                    word += ' '
                line += word
                word = ''

                #empty line
                if char == "\n" and len(line.lstrip()) == 0:
                    line = ''

            if pair_required == False:
                #add word to line
                if char == ";" or char == "{" or  char == "}":
                    #end of line:
                    #find indent
                    #remove whitespace and newline
                    line += word
                    word = ''


                    line = line.lstrip().strip()
                    if len(line) > 0:
                        #send line to the parse line
                        string_to_write = self.parse_line(line, loop)
                        string_to_write = self.preprocessor.check_macros(string_to_write)
                        self.printer.fprint(string_to_write)
                        if char == "{" and line.split()[0] in self.types and line.split()[1][-1] == "]":
                            self.printer.unindent()
                            print(line)
                        line = ''
                        word = ''
                        loop = None

                    if char == "{":

                        self.printer.indent()

                    if char == "}":
                        self.printer.unindent()

            

    #parse_line
    #parses through the line sent from main parse loop

    #line: line to parse through
    #loop: possible loop in line

    #returns the string for the printer to add to the file
    def parse_line(self, line, loop):
        line = line.lstrip()

        #check last character of the line
        if line[-1] == ";":    
            #definition
            pass
        elif line[-1] == "{":
            #loop or function
            pass

        #check for some sort of funciton in the line:

        func_present, func_name = self.find_func(line)

        #find what to do with line
        if line.lstrip()[-1] == "}" and len(line.lstrip()) == 1:
            #end of the scope dont print anything
            string_to_write = ''
        elif loop != None:
            #loop is present - convert it
            string_to_write = loop_converter(line, self.printer.get_indent()).convert(loop)


        # elif line.lstrip().split[0] == "struct":
        #     #something to dod with structs
        #     if line[-1] == ';':
        #         #instance declaration
        #         string_to_write = self.struct_converter().declare_instance(line)

        #     if line [-1] == "{":
        #         #struct definition
        #         string_to_write = self.struct_converter().define_struct(line)
        #         self.struct_definition = true

        elif line.split()[0] in self.types:
            #its a declaration
            #pass type
            pos = self.find_first_whitespace(line)
            #find name
            pos = self.find_first_char(line, pos)
            #check characters:
            i = pos
            func_dec = False
            while i < len(line) and (self.check_char(line[i]) or line[i].isspace()):
                if line[i+1] == "(":
                    #its a function
                    func_dec = True
                    func_name = line[pos:pos+i]
                i += 1

            if func_dec:
                if line[-1] == ";":
                    #its a declaration and can be ignored
                    string_to_write = ''
                else:
                                        #not a declaration convert the function
                    string_to_write = function(line).declare()
                    self.function_converter.add_func(func_name)
                
            elif not func_dec:

                #variable declaration
                string_to_write = variable(line, self.c_file, self.printer).declare(self.printer.get_indent())
                if func_present:
                    #convert function call
                    string_to_write = self.function_converter.convert(string_to_write, self.printer.get_indent())

        elif func_present:
            #convert the function call
            string_to_write = self.function_converter.convert(line, self.printer.get_indent())
        
        elif line.lstrip()[:6] == "return":
            #gets rid of the newline character attached to return
            string_to_write = line[:line.find(";")]

        elif line.lstrip()[:4] == "else":
            string_to_write = "else:"
        else:
            #nothing to be done. remove the end of line character
            string_to_write = line[:line.find(";")]        

        return string_to_write


    #find_indent
    #finds the indent of the c_file
    #not used anymore
    def find_indent(self, line):
        i = 0
        indent = 0
        while line[i:i+4] == "    " or line[i] == chr(9):
            indent += 1
            i += 4
        return indent
        #indent = (len(line) - len(line.lstrip()))/4
        return indent


    #find_first_whitespace
    #finds the first instance of whitespace from a given point

    #line: line to search for whitespace
    #start: location to start search from, default is beggining of the line

    #returns location of whitespace. if none is found returns -1
    def find_first_whitespace(self, line, start = 0):
        for i in range(start, len(line)):
            if line[i].isspace():
                return i 
        return(-1)


    #find_first_char
    #finds the first instance of a character from a given point

    #line: line to search for character
    #start: location to start search from, default is beggining of the line

    #returns location of character. if none is found returns -1
    def find_first_char(self, line, start = 0):
        for i in range(start, len(line)):
            if line[i].isalpha():
                return i
        return(-1)


    #altparse
    #alternative parser
    #not used anymore
    def altparse(self):
        lines = self.c_file.readlines()
        for i, line in enumerate(lines):
            #find indent
            self.printer.set_indent(self.find_indent(line))

            #remove whitespace and newline
            line = line.lstrip().strip()
            if len(line) > 0:
                string_to_write = self.parse_line(line)
                self.printer.fprint(string_to_write)


################################################
##old transpiler unused
################################################

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
