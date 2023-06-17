class pet:
	def __init__(self, name, age, species, housetrained):
		self.name = name
		self.nicknames = []
		self.age = age
		self.species = species
		self.housetrained = housetrained

	def add_nickname(self, nickname):
		if self.has_nickname(nickname):
			print("{} already a nickname".format(nickname))
			return("fail")

		else:
			self.nicknames.append(nickname)
			return "success"

	def has_nickname(self, nickname):
		if nickname in self.nicknames:
			return True
		else:
			return False