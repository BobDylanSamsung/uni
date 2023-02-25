class loop:
    def __init__(self, line, indent):
        self.line = line

    def convert(self, loop):
        func_to_call = self.find_loop(loop)
        string_to_write = func_to_call(self.line)
        return(string_to_write)

    def find_loop(self, name):
        if name == "while":
            return self.convert_while

    def convert_while(self, line):
        pos = line.find("while") + len("while")

        whitespace = 0

        while line[pos].isspace():
            line = line[:pos] + line[pos+1:]

        return line[:-1] + ":"

line = '''while       (x<2){'''

print(loop(line).convert("while"))