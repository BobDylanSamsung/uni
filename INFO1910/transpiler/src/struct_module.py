class Struct_Converter():
    def __init__(self):
        pass

    def convert(self, line):
        string_to_write = self.declare_instance(line)
        return string_to_write

    def declare_instance(self, line):
        struct_type = line[:-1].split()[1]
        name = line[:-1].split()[2]
        string_to_write = '''{} = {}()'''.format(name, struct_type)
        return string_to_write
