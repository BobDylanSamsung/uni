import sys
from src.variable_module import variable
from src.transpiler_module import basic_transpiler as transpiler
from src.pointer_module import pointer
from src.printer_module import printer
from src.function_module import function
from src.loop_module import loop_converter


c_file = open("tests/c_files/for/case_5/case.c", "rb")
py_file = open("out.py", "w")



transpiler = transpiler(c_file, py_file)

transpiler.parse()

py_file.close()

c_file.close()
