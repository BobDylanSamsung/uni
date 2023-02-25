length = int(input("Enter length: "))

numbers = [0]

i = 1

cur = 1
prev = 0

while i < length:
    numbers.append(cur)
    temp = cur
    cur += prev
    prev = temp
    i += 1

for i in numbers:
    print(i, end = "\t")

print(numbers[-1]/numbers[-2])