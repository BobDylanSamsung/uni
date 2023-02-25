
#object to emulate the effects of pointers
class pointer:
    #initialise
        #value: value of the "pointer"
	def __init__(self, value):
		self.value = self.change_val(value)

    #change_val
    #changes the value of the pointer

    #value: value to change to
	def change_val(self, value):
		self.value = value


    #get value
    #returns the value of the pointer
	def get_val(self):
		return self.value