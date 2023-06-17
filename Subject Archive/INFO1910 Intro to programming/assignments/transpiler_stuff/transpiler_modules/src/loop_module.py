class loop_converter:
    def __init__(self, line, indent):
        self.line = line
        self.indent = indent

    def convert(self, loop):
        func_to_call = self.find_loop(loop)
        string_to_write = func_to_call(self.line)
        return(string_to_write)

    def find_loop(self, name):
        if name == "while":
            return self.convert_while

        if name == "for":
            return self.convert_for

    def convert_while(self, line):
        pos = line.find("while") + len("while")

        whitespace = 0

        while line[pos].isspace():
            line = line[:pos] + line[pos+1:]

        return line[:-1] + ":"

    def convert_for(self, line):
        begin = line.find("(") + 1
        end = line.find(")")
        parameters = line[begin:end].split(";")

        definition = ' '.join(parameters[0].split()[1:]).lstrip()

        condition = '    ' * self.indent + "while "+ parameters[1].lstrip()

        change = parameters[2].lstrip().strip()

        if change[-2:] == "++":
            change = '    ' * (self.indent + 1) + change[0] + " += 1"
            definition += "-1"
        elif change[-2] == "+":
            change = '    ' * (self.indent + 1) + change[0] + " += 1"

        if change[-2:] == "--":
            change = '    ' * (self.indent + 1) + change[0] + " -= 1"
            definition += "+1"

        elif change[-2] == "-":
            change = '    ' * (self.indent + 1) + change[0] + " -= 1"

        string_to_write = ("{}\n{}:\n{}".format(definition, condition, change))

        return string_to_write
