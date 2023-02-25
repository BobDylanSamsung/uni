def factorial(x, total=1):
	if x <= 1:
		return total
	else:
		total *= x
		x -= 1
		return factorial(x, total=total)


def bin_coefficients(n, k):
	


x = factorial(5)

print(x)

