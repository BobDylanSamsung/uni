def factorial(n):
    i = 1
    prev = 1
    while i <= n:
        prev *= i
        yield prev
        i +=1 


fn = factorial(10)

for i in fn:
    print(i)
