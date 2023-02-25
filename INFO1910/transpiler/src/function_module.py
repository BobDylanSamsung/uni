#converts the first line of a function definition
class function():
    #initialise
        #line: line to read from
        #scope_open: amount of { characters passed
        #scope_close: amount of } characters passed
    def __init__(self, line):
        self.line = line
        self.scope_open = 0
        self.scope_close = 0


    #declare
    #general dispatch function for all function declarations

    #returns the string to write to the file
    def declare(self):
        name, parameters= self.tokenise(self.line)
        string_to_write = "def {}{}:\n".format(name, parameters)
        return string_to_write

    #parser
    #parses through the line inputted

    #returns the string to write to the file
    def parser(self):
        for num, line in enumerate(self.lines):
            if num == 0:
                #declare function
                line_to_write = self.declare(line)

            else:
                #parse through function
                varible()


            return string_to_write

    #tokenise
    #finds the name and the parameters of the function

    #line: line containing the function

    #returns the name and the parameters
    def tokenise(self, line):
        bracket_open = line.find("(")
        bracket_close = line.find(")")
        parameters = line[bracket_open:bracket_close+1]

        parameters = self.parse_parameters(parameters)

        line = line.lstrip()
        pos = self.find_first_whitespace(line)
        pos = self.find_first_char(line, pos)

        name = line[pos:bracket_open]
        if name == "main":
            parameters = "(argc, argv)"


        return(name, parameters)


    #parse_parameters
    #parses through the parameters and converts them to python syntax

    #parameters: parameters to parse through

    #returns the formatted parameters
    def parse_parameters(self, parameters):
        #expects parameters to be (*type name,)
        parameters = parameters[1:-1]
        new_params = []
        for param in parameters.split(','):
            if param != '':
                #add second word of each parameter which is the name
                new_params.append(param.split()[1])
        parameters = "(" + ", ".join(new_params) + ")"
        return parameters

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



#function converter
#converts a function call in a line to python
class Function_Converter():
    #initialise
        #user_funcs: all of the user defined funcs will be added
        #lib_funcs: all of the library functions able to be transpiled and the name of the corresponding submodule
        #loop_funcs: loops that may be confused as functions and can still be handled        
    def __init__(self):
        self.user_funcs = []
        self.lib_funcs = {
        "printf": "print",
        "scanf": "input",
        "atoi": "int"
        }
        self.loop_funcs = {
        "while": "convert_while",
        "for": "convert_for",
        "if": "convert_if",
        }


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


    #convert
    #general dispatch function always called

    #line: line to convert
    #indent: current indentation of the line

    #returns string to write to file
    def convert(self, line, indent):
        words = line.split()
        string_to_write = line
        for word in words:
            for i in range(len(word)-1):
                if self.check_char(word[i]) and word[i+1] == "(":
                    string_to_write = self.change_func(word[:i+1], string_to_write, indent)
        return string_to_write


    #add_func
    #adds function to user defined library

    #func: name of the function

    #returns nothing
    def add_func(self, func):
        self.user_funcs.append(func)




    #change_func
    #dispatch function to convert either loop or library function

    #func: name of the function to convert
    #line: line to be converted
    #indentation: current indentation of the line

    #returns the line to print to the file
    def change_func(self, func, line, indent):
        if func in self.loop_funcs:
            line = self.standard_func(line, self.loop_funcs[func], indent)
        if func in self.lib_funcs:
            line = self.standard_func(line, func, indent)

        return line


    #standard_func
    #dispatch funciton to call specific function module

    #line: line containing the function
    #func: name of the funciton in the line
    #indent: current indentation of the line

    #returns the string to write to the file
    def standard_func(self, line, func, indent):
        string_to_write = self.__getattribute__(func).__call__(line, indent)
        return string_to_write


    #printf
    #converts printf to print

    #line: line to convert
    #indent: current indentation of line

    #returns string to write to file
    def printf(self, line, indent):
        string_to_write = line.replace("printf(", "print(", 1)
        string_to_write = self.format_string(string_to_write, "print")
        return string_to_write



    #atoi
    #converts atoi to int

    #line: line to convert
    #indent: current  indentation

    #returns string to write to file
    def atoi(self, line, indent):
        string_to_write = line.replace("atoi(", "int(")
        return string_to_write


    #scanf
    #converts scanf to input

    #line: line to convert
    #indent: current  indentation

    #returns string to write to file
    def scanf(self, line, indent):
        string_to_write = "line = input()\n" 

        quote_open = line.find('"')
        quote_close = quote_open+1
        while quote_close < len(line) and line[quote_close] != '"':
            quote_close += 1

        bracket_close = line.rfind(")")

        format_characters = line[quote_open+1:quote_close]

        variables = line[quote_close + 1: bracket_close].lstrip()
        variables = variables[1:].split(",")
        for i, var in enumerate(variables):
            var = var.lstrip().strip()
            name_start = 0
            while name_start < len(var) and not (var[name_start].isalpha() or var[name_start] != "_"):
                name_start += 1        
            variables[i] = var[name_start+1:]



        i = 0
        count = 0
        while i < len(format_characters)-1:

            if format_characters[i] == "%":
                if format_characters[i+1] == "d":
                    string_to_write += '''{}{} = int(line.split()[{}])\n'''.format("    "*indent, variables[count], count)
                if format_characters[i+1] == "f":
                    string_to_write += '''{}{} = float(line.split()[{}])\n'''.format("    "*indent, variables[count], count)
                if format_characters[i+1] == "s":
                    string_to_write += '''{}{} = str(line.split()[{}])\n'''.format("    "*indent, variables[count], count)
                if format_characters[i+1] == "c":
                    string_to_write += '''{}{} = str(line.split()[{}])\n'''.format("    "*indent, variables[count], count)
                count += 1
            i += 1

        return string_to_write




    #format_string
    #converts formatting characters in c to python

    #line: line to convert
    #indent: current  indentation

    #returns string to write to file
    def format_string(self, line, func):
        line = line.replace("\n", "\\n")
        line = line.replace("\t", "\\t")

        if line[-1] == ';':
            line = line[:-1]
        i = line.find("print" + "(") + len("print" + "(")




        count = 0

        while i < len(line) and count < 2:
            if line[i] == '"':
                count += 1
            i += 1

        #check for formatting characters:
        index = i
        format_characters_present = False



        if line[index] == ",":
            format_characters_present = True
            index += 1

        else:
            while line[index].isspace():
                if line[index] == ",":
                    format_characters_present = True
                index += 1


        if format_characters_present:
            line =  (line[:i].replace("%c", "%s") + "%(" + line[i+1:] + ''', end = "")''')

        else:
            line = line[:-1] + ''', end = "")'''

        return line



    #convert_while
    #converts while loops registered as a function

    #line: line to convert
    #indent: current  indentation

    #returns string to write to file
    def convert_while(self, line, indent):
        return line[:-1].strip() + ":"


    #convert_for
    #converts for loops registered as functions
    #line: line to convert
    #indent: current  indentation

    #returns string to write to file
    def convert_for(self, line, indent):
        begin = line.find("(") + 1
        end = line.find(")")
        parameters = line[begin:end].split(";")

        definition = ' '.join(parameters[0].split()[1:]).lstrip()

        condition = '    ' * indent + "while "+ parameters[1].lstrip()

        change = parameters[2].lstrip().strip()

        check = '    ' * (indent + 1) + "if not {}: break".format(parameters[1].lstrip())
        if change[-2:] == "++":
            change = '    ' * (indent + 1) + change[0] + " += 1"
            definition += "-1"

        elif change[:2] == "++":
            change = '    ' * (indent + 1) + change[2] + " += 1"
            definition += "-1"

        if change[-2:] == "--":
            change = '    ' * (indent + 1) + change[0] + " -= 1"
            definition += "+1"
        elif change[:2] == "--":
            change = '    ' * (indent + 1) + change[2] + " -= 1"
            definition += "+1"


        string_to_write = ("{}\n{}:\n{}\n{}".format(definition, condition, change, check))

        return string_to_write


    #convert_if
    #module to convert if statements to python

    #line: line containing if statement

    #returns the string to write to the file
    def convert_if(self, line, indent):
        if line[:4] == "else":
            line = "el" + line[line.find("if"):]
        line = line[:-1].strip() + ":"
        return line




