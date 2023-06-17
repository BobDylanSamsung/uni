from pet import pet

lucy = pet("lucy", 2, "dog", False)

lucy.add_nickname("girrl")
lucy.add_nickname("bitch")
lucy.add_nickname("shmoos")

print(lucy.has_nickname("girrl"))
print(lucy.has_nickname("luigi"))
