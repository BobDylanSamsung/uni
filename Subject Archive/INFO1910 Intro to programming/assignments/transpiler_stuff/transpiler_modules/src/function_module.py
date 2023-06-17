class function():
    def __init__(self, line):
        self.line = line
        self.scope_open = 0
        self.scope_close = 0

    def declare(self):
        name, parameters= self.tokenise(self.line)
        string_to_write = "def {}{}:\n".format(name, parameters)
        return string_to_write


    def parser(self):
        for num, line in enumerate(self.lines):
            if num == 0:
                #declare function
                line_to_write = self.declare(line)

            else:
                #parse through function
                varible()


            return string_to_write


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


class function_converter():
    def __init__(self, indent = 0):
        self.indent = indent
        self.user_funcs = []
        self.lib_funcs = {
        "printf": "print",
        "scanf": "input",
        "while": "convert_while",
        "for": "convert_for"
        }

    def check_char(self, char):
        acceptable = False

        if char.isalpha():
            acceptable = True

        if char.isdigit():
            acceptable = True

        if char == "_":
            acceptable = True

        return acceptable

    def convert(self, line):
        words = line.split()
        string_to_write = line
        for word in words:
            for i in range(len(word)-1):
                if self.check_char(word[i]) and word[i+1] == "(":
                    string_to_write = self.change_func(word[:i+1], string_to_write)
        if string_to_write[-1] == ";":
            string_to_write = string_to_write[:-1]
        return string_to_write

    def add_func(self, func):
        self.user_funcs.append(func)

    def change_func(self, func, line):
        if func in self.lib_funcs:
            print(func)
            string_to_write = self.standard_func(line, func)
            return string_to_write

    def standard_func(self, line, func):
        string_to_write = self.__getattribute__(func).__call__(line)
        #string_to_write = line.replace(func, self.lib_funcs[func])
        return string_to_write

    def printf(self, line):
        print("RUNNING")
        string_to_write = line.replace("printf(", "print(", 1)
        string_to_write = self.format_string(string_to_write, "print")
        return string_to_write

    def format_string(self, line, func):
        line = line.replace("\n", "\\n")
        line = line.replace("\t", "\\t")

        if line[-1] == ';':
            line = line[:-1]
        i = line.find(func + "(") + len(func + "(")

        print("FUCKFUCKFUCK",line)



        count = 0

        while i < len(line) and count < 2:
            if line[i] == '"':
                count += 1
            i += 1

        #check for formatting characters:
        index = i
        format_characters_present = False

        while line[index].isspace():
            if line[index+1] == ",":
                format_characters_present = True

        if format_characters_present:
            return (line[:i] + "%(" + line[i+1:] + ")")

        else:
            return line



    def convert_while(self, line):
        return line[-1] + ":"

    def convert_for(self, line):
        begin = line.find("(") + 1
        end = line.find(")")
        parameters = line[begin:end].split(";")

        definition = '    ' * self.indent + ' '.join(parameters[0].split()[1:]).lstrip()

        condition = '    ' * self.indent + parameters[1].lstrip()

        change = '    ' * (self.indent + 1) + parameters[2].lstrip()
        if change[-2:] == "++":
            change = "x += 1"
            definition += "-1"

        if change[-2:] == "--":
            change = "x -= 1"
            definition += "+1"
        
        string_to_write = ("{}\nwhile {}:\n{}".format(definition, condition, change))

        return string_to_write







