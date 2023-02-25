class TypedList:
    def __init__(self, _type):
        self.type = type(_type)
        self.values = []
    
    def check_type(self, element):
        if type(element) != self.type:
            raise TypeError("Incompatible type")

    def append(self, element):
        self.check_type(element)
        self.values.append(element)


        
    def prepend(self, element):

        self.check_type(element)
        new_vals = [element]
        for item in self.values:
            new_vals.append(item)
        return new_vals

    
    def insert(self, index, element):

        self.check_type(element)
        while index < len(self.values):
            temp = self.values[index]
            self.values[index] = element
            element = temp
            index += 1

        self.values.append(element)

    
    def get(self, index):

        return self.values[index]

    def remove(self, index):

        start = self.values[:index]
        end = self.values[index+1:]

        self.values = start + end

    def iter(self):
        return iter(self.values)


tl = TypedList(4)

for i in [1,3,5,2,77,321]:
    tl.append(i)

x = tl.iter()

print(next(x))
print(next(x))
print(next(x))
print(next(x))
