import sys
def fib(x):
    if x == 0:
        return 0

    total = 1
    prev = 0

    while x > 0:
        temp = total
        total += prev
        prev = temp
        x -= 1

    return total

print(fib(int(sys.argv[1])))