class variable:
    def __init__(self, line):
        self.line = line
        self.var_type = self.find_type(line)
        print("var type is: ", self.var_type)
        self.dec_func = self.find_dec_func(self.var_type)

    def declare(self, indent):
        func_to_call = self.find_dec_func(self.var_type)
        line = self.format_line()

        string_to_write = func_to_call(line, indent)
        return string_to_write

    def format_line(self):
        #removes type and spaces from the left hand side of the line
        line = self.line.split()
        line = " ".join(line[1:])
        return(line)


    def find_type(self,line):
        #type is first word of line
        for char in line:
            if char == '*':
                print("THIS IS A POINTER")
        return line.split()[0]

    def find_dec_func(self, var_type):
        int_types = ["int", "long"]
        str_types = ["char"]
        float_types = ["float"]


        if var_type in str_types:
            print("calling str func")
            call = self.dec_str



        elif var_type in int_types:
            call = self.dec_int



        elif var_type in float_types:
            call = self.dec_float

        return(call)








    def dec_float(self, line, indent):
        print("hellooooooooooooooooooooooo")
        name = ''
        value = ''
        string_to_write  = ''
        assignment_found = False
        brackets_open = 0
        brackets_closed = 0

        for character in line:
            if (character != ";" and character != ",") or brackets_open != brackets_closed:

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



            elif brackets_open == brackets_closed:
                if assignment_found == False:
                    #empty value
                    value = "None"

                #write to file
                print(name,value)
                string_to_write += "{} = float({})\n".format(name, value)
                
                #reset parameters
                name = '    '*indent
                value = ''
                assignment_found = False
        print("returning: ", string_to_write)

        return(string_to_write)









    def dec_int(self, line, indent):
        name = ''
        value = ''
        string_to_write  = ''
        assignment_found = False
        brackets_open = 0
        brackets_closed = 0

        for character in line:
            if (character != ";" and character != ",") or brackets_open != brackets_closed:

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



            elif brackets_open == brackets_closed:
                if assignment_found == False:
                    #empty value
                    value = "None"

                #write to file
                string_to_write += "{} = int({})\n".format(name, value)
                
                #reset parameters
                name = '    '*indent
                value = ''
                assignment_found = False
        print("returning: ", string_to_write)

        return(string_to_write)


    def dec_str(self, line, indent):
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
                    value = "None"

                string_to_write += "{} = str({})\n".format(name, value)
                name = '    '*indent
                value = ''
                assignment_found = False
        print("returning: ", string_to_write)
        return string_to_write





# def dec_int(line, py_file):
#   word = 1
#   name = ''
#   value = ''
#   assignment_found = False

#   for character in line:
#       if character == ' ':
#           word += 1

#       elif word > 1:
#           if character != ";" and character != ",":
#               if character == "=":
#                   assignment_found = True

#               elif assignment_found == False:
#                   name += character

#               elif assignment_found == True:
#                   value += character

#           else:
#               if assignment_found == False:
#                   value = "None"
#               py_file.write("{} = int({})\n".format(name, value))
#               name = ''
#               value = ''
#               assignment_found = False

# def dec_str(line, py_file):
#   print("line is: \t", line)

#   word = 1
#   name = ''
#   value = ''
#   assignment_found = False
#   quote_open = False
#   opener = ''

#   for character in line:
#       if character == ' ':
#           word += 1

#       elif word > 1:
#           if character != ";" and character != ",":
#               if character == "=":
#                   assignment_found = True

#               elif assignment_found == False:
#                   name += character

#               elif assignment_found == True:
#                   value += character

#               elif character == "'" or character == '"' and quote_open == False:
#                   quote_open = True
#                   opener = character

#               elif character == opener and quote_open == True:
#                   quote_open == False

#           elif quote_open == True:
#               value += character

#           else:
#               if assignment_found == False:
#                   value = "None"

#               print("{} = str({})\n".format(name, value))

#               py_file.write("{} = str({})\n".format(name, value))
#               name = ''
#               value = ''
#               assignment_found = False



# c_file = open("char_dec.c", "r")

# py_file = open("out.py", "w")

# lines = c_file.readlines()

# for line in lines:
#   declaration =  var_dec(line, py_file)





# def dec_str(line, py_file):
#   pass

# def dec_float(line, py_file):
#   pass

# def dec_var(name, value, var_type)
