class printer():
    def __init__(self, output_file):
        self.indentation = 0
        self.output_file = output_file

    def fprint(self, line):
        print("printing", line)
        self.output_file.write("    "*self.indentation + line + '\n')

    def oprint(self, line):
        print("    "*self.indentation + line)

    def indent(self):
        self.indentation += 1

    def unindent(self):
        self.indentation -= 1

    def set_indent(self, value):
        self.indentation = value

    def get_indent(self):
        return self.indentation