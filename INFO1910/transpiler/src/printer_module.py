#printer object for printing to fle
class Printer():
    #initialise
        #indentation: current indentation
        #output_file: python file to write to
    def __init__(self, output_file):
        self.indentation = 0
        self.output_file = output_file

    #fprint
    #prints line to file

    #line: line to print to file
    def fprint(self, line):
        self.output_file.write("    "*self.indentation + line.lstrip() + '\n')

    #oprint
    #prints to standard output

    #line: line to print to stdout
    def oprint(self, line):
        print("    "*self.indentation + line)

    #indent
    #increases indent
    def indent(self):
        self.indentation += 1

    #inindent
    #decreased indent
    def unindent(self):
        self.indentation -= 1

    #set indent
    #sets indent to a value

    #value: value to set indent to
    def set_indent(self, value):
        self.indentation = value

    #get_indent
    #returns the value of the current indent
    def get_indent(self):
        return self.indentation