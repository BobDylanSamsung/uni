import os

#module to emulate the effects of the preproccessor
class Preprocessor:
    #initialise:
        #directory: name of the directory of hte c_file
        #subdirs: subdirectories that may be entered during linking
        #printer: printer module
        #macro_table: dictionary of macros and their values
        #py_file: file to output to
        #transpiler: transpiler module for including other files
        #depth: depth of the files to include
    def __init__(self, printer, py_file, c_file, transpiler):
        self.directory = c_file.name[:c_file.name.rfind("/")+1]
        self.subdirs = []
        self.printer = printer
        self.macro_table = {}
        self.py_file = py_file
        self.transpiler = transpiler
        self.depth = 0

    #convert
    #general dipatch function called when preprocessor is used

    #line: line to convert

    #returns if a header guard was activated
    def convert(self, line):
        guard = False
        if line.split()[0] == "#ifndef":
            guard = self.header_guard(line)
        if line.split()[0] == "#define":
            self.define_macro(line)
        if line.split()[0] == "#include" and line.split()[1][0] == '"':
                self.include_file(line)
        return guard


    #header_guard
    #checks if a header guard is activated through the macro table

    #line: lien containing the headerguard

    #returns if the macro is alread defined
    def header_guard(self, line):
        line = line.split()
        if line[1] in self.macro_table:
            return(True)
        else:
            return(False)


    #define macro
    #adds macro to the macro table

    #line: line with macro
    def define_macro(self, line):
        line = line.split()
        if len(line)> 2:
            self.macro_table[line[1]] = line[2]
        else:
            self.macro_table[line[1]] = line[1]


    #include_file
    #calls the transpiler on a file to be included

    #line: line specifying the file
    def include_file(self, line):
        file = line.split()[1][1:-1]

        #checks if a subdirectory is present
        if file.rfind("/") > 0:
            #subdirectory present
            #add subdirectory to the subdirectory array and get the name of the file
            subdirectory = file[:file.rfind("/")+1]
            self.subdirs.append(subdirectory)
            name = file[file.rfind("/")+1:]
        else:
            #no subdirectory is present just get the name of the file
            subdirectory = ''
            name = file

        #set path
        path_to_file = self.directory + "".join(self.subdirs) + name
        #open file
        c_file = open(path_to_file, "r")


        #calls the transpiler for the file

        self.transpiler.parse(c_file)

        c_file.close()

        #if a subdirectory was present remove it at completion of file call
        if len(subdirectory) > 0:
            self.subdirs = self.subdirs[:-1]

    #check_macros
    #replaces defined macros with their value

    #line: line to check for macros

    #returns line with macros changed
    def check_macros(self, line):
        for macro in self.macro_table:
            line = line.replace(macro, self.macro_table[macro])
        return line