def m_range(*args):
    if len(args) < 1 or len(args) > 2:
        raise ValueError("Incorrect number of arguments")
    elif len (args) == 1:
        end = args[0]
        start = 0
    else:
        if args[0] > args[1]:
            end = args[0]
            start = args[1]
        else:
            end = args[1]
            start = args[0]

    while start < end:
        yield start
        start += 1

n = m_range(10,4)

print(n.__next__())
print(n.__next__())
print(n.__next__())
print(n.__next__())
print(n.__next__())
print(n.__next__())
print(n.__next__())
print(n.__next__())