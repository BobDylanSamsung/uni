import sys
from src.transpiler_module import basic_transpiler
from src.printer_module import Printer



c_files = []

i = 1
#allocate files
while i < len(sys.argv):
    if sys.argv[i][-3:] == ".py":
        py_file = open(sys.argv[i], "w")
    else:
        c_files.append(sys.argv[i])

    i += 1

#create variables for objects
printer = Printer(py_file)
transpiler = basic_transpiler(py_file, printer)


printer.fprint("import sys")

#transpile all c files passed
for file in c_files:
    filestream = open(file, "r")

    transpiler.set_c_file(filestream)

    transpiler.parse()

    filestream.close()


printer.set_indent(0)
printer.fprint("CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)")

py_file.close()

