class pointer:
	def __init__(self, value):
		self.value = self.change_val(value)

	def change_val(self, value):
		self.value = value

	def get_val(self):
		return self.value