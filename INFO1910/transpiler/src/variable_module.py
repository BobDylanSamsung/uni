#variable module for varible declarations
class variable:
    #initialise
        #line: line to convert
        #var_type: type of variable declared
        #dec_func: submodule to call for that particular type
        #c_file: file stream to read from
        #printer: printer module to output to file
    def __init__(self, line, c_file, printer):
        self.line = line
        self.var_type = self.find_type(line)
        self.dec_func = self.find_dec_func(self.var_type)
        self.c_file = c_file
        self.printer = printer

    #declare
    #general dispatch function called to declare a variable

    #indent: current indentation

    #returns the string to write to the file
    def declare(self, indent):
        func_to_call = self.find_dec_func(self.var_type)
        line = self.format_line()

        string_to_write = func_to_call(line, indent)
        return string_to_write



    #format_line
    #removes type and whitespace from the left hand side of the line
    #returns the formatted line
    def format_line(self):
        line = self.line.split()
        line = " ".join(line[1:])
        return(line)



    #find_type
    #finds the type of the variable declared

    #line: line containing the declaration

    #returns the type
    def find_type(self,line):
        #type is first word of line
        for char in line:
            if char == '*':
                pass
        return line.split()[0]



    #find_dec_func
    #finds the submodule to call to define that variable

    #var_type: type of variable declared

    #returns the submodule
    def find_dec_func(self, var_type):
        int_types = ["int", "long"]
        str_types = ["char"]
        float_types = ["float"]


        if var_type in str_types:
            call = self.dec_str



        elif var_type in int_types:
            call = self.dec_int



        elif var_type in float_types:
            call = self.dec_float

        return(call)







    #dec_float
    #submodule to declare a float

    #line: line containing declaration
    #indent: current indentation

    #returns a string containing theconverted declaration
    def dec_float(self, line, indent):
        #initialise variables
        name = ''
        value = ''
        string_to_write  = ''
        assignment_found = False
        brackets_open = 0
        brackets_closed = 0

        for character in line:
            if (character != ";" and character != "," and character != "{") or brackets_open != brackets_closed:

                if character == "(":
                    brackets_open += 1

                elif character == ")":
                    brackets_closed += 1
                

                if character == "=":
                    assignment_found = True

                elif assignment_found == False and character != ' ':
                    #Add current character to name
                    name += character

                elif assignment_found == True:
                    #Add current character to value
                    value += character



            elif brackets_open == brackets_closed or character == "{":
                if assignment_found == False:
                    #empty value
                    value = 0

                if name.strip()[-1] == "]":
                    #array present
                    name, value = self.convert_array(name, value, assignment_found)
                    string_to_write += "{} = {}\n".format(name, value)


                else:
                    #write to file
                    string_to_write += "{} = float({})\n".format(name, value)
                
                #reset parameters
                name = '    '*indent
                value = ''
                assignment_found = False

        return(string_to_write)








    #dec_int
    #converts int declaration to python syntax

    #line: line containing declaration
    #indent: current indentation

    #returns a string containing theconverted declaration
    def dec_int(self, line, indent):
        #initialise variables
        name = ''
        value = ''
        string_to_write  = ''
        assignment_found = False
        brackets_open = 0
        brackets_closed = 0

        for character in line:
            if (character != ";" and character != "," and character != "{") or brackets_open != brackets_closed:
                if character == "(":
                    brackets_open += 1

                elif character == ")":
                    brackets_closed += 1
                

                if character == "=":
                    assignment_found = True

                elif assignment_found == False and character != ' ':
                    #Add current character to name
                    name += character

                elif assignment_found == True:
                    #Add current character to value
                    value += character



            elif brackets_open == brackets_closed or character == "{":
                if assignment_found == False:
                    #empty value
                    value = 0

                if name.strip()[-1] == "]":
                    #array present
                    name, value = self.convert_array(name, value, assignment_found)
                    string_to_write += "{} = {}\n".format(name, value)


                else:
                    #write to file
                    string_to_write += "{} = int({})\n".format(name, value)
                


                #reset parameters
                name = '    '*indent
                value = ''
                assignment_found = False

        return(string_to_write)


    #dec_str
    #converts string or character declaration to python syntax

    #line: line containing declaration
    #indent: current indentation

    #returns a string containing theconverted declaration
    def dec_str(self, line, indent):
        #initialise variables
        name = ''
        value = ''
        assignment_found = False
        quote_open = False
        opener = ''
        string_to_write  = ''
        brackets_open = 0
        brackets_closed = 0

        for character in line:
            if character != ";" and character != "," and quote_open == False or brackets_open != brackets_closed and quote_open == False:
                if character == "(":
                    brackets_open += 1

                elif character == ")":
                    brackets_closed += 1




                if character == "=":
                    assignment_found = True

                elif assignment_found == False and character != ' ':
                    #add current character to name
                    name += character

                elif assignment_found == True:
                    #add current character to value
                    value += character

                elif (character == "'" or character == '"') and quote_open == False:
                    #string is starting end characters can be included
                    quote_open = True
                    opener = character

                elif character == opener and quote_open == True:
                    #Close quote when terminating character is reached
                    quote_open == False

            elif quote_open == True:
                value += character

            elif brackets_open == brackets_closed:
                if assignment_found == False:
                    #empty value
                    value = ''

                string_to_write += "{} = str({})\n".format(name, value)
                name = '    '*indent
                value = ''
                assignment_found = False
        return string_to_write



    #convert_array
    #converts array declaration to python sytax

    #name: name of the varibale
    #value: value to be set to
    #assignment_found: boolean value dictating if a value was specified

    #returns the new name and value
    def convert_array(self, name, value, assignment_found):
        bracket_open = name.find("[")
        name = "    " + name[:bracket_open]

        char = self.c_file.read(1)

        while char != "}":
            value += char
            char = self.c_file.read(1)

        if assignment_found:
            value = "[" + value.strip().lstrip() + "]" 

        else:
            value = "[]"

        return name, value


