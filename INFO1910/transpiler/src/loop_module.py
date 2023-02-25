class loop_converter:
    #initialise
        #line: current line to transpile
        #indent: current indentation
    def __init__(self, line, indent):
        self.line = line
        self.indent = indent

    #convert
    #general dispatch function to convert loops

    #loop: name of the loop found

    #returns the line to write to file
    def convert(self, loop):
        func_to_call = self.find_loop(loop)
        string_to_write = func_to_call(self.line)
        return(string_to_write)

    #find_loop
    #returns module for a articular loop

    #name: name of the loop

    #returns the module
    def find_loop(self, name):
        if name == "while":
            return self.convert_while

        if name == "for":
            return self.convert_for

        if name == "if":
            return self.convert_if

        if name == "else":
            return self.convert_else



    #convert_if
    #module to convert if statements to python

    #line: line containing if statement

    #returns the string to write to the file
    def convert_if(self, line):
        if line[:4] == "else":
            line = "el" + line[line.find("if"):]
        line = line[:-1].strip() + ":"
        return line



    #convert_while
    #module to convert while loop to python

    #line: line containing the loop

    #returns the string to write to the file
    def convert_while(self, line):
        pos = line.find("while") + len("while")

        whitespace = 0

        while line[pos].isspace():
            line = line[:pos] + line[pos+1:]

        return line[:-1] + ":"

    #convert_for
    #module to convert for loop to python

    #line: line containing the loop

    #returns the string to write to the file        
    def convert_for(self, line):
        begin = line.find("(") + 1
        end = line.find(")")
        parameters = line[begin:end].split(";")

        definition = ' '.join(parameters[0].split()[1:]).lstrip()

        condition = '    ' * self.indent + "while "+ parameters[1].lstrip()

        change = parameters[2].lstrip().strip()

        check = '    ' * (self.indent + 1) + "if not {}: break".format(parameters[1].lstrip())
        if change[-2:] == "++":
            change = '    ' * (self.indent + 1) + change[0] + " += 1"
            definition += "-1"

        elif change[:2] == "++":
            change = '    ' * (self.indent + 1) + change[2] + " += 1"
            definition += "-1"

        if change[-2:] == "--":
            change = '    ' * (self.indent + 1) + change[0] + " -= 1"
            definition += "+1"
        elif change[:2] == "--":
            change = '    ' * (self.indent + 1) + change[2] + " -= 1"
            definition += "+1"


        string_to_write = ("{}\n{}:\n{}\n{}".format(definition, condition, change, check))

        return string_to_write
