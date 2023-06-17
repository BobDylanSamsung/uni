ls = [1,4,9,16,25]

iter_obj = ls.__iter__()

while True:
    try:
        x = iter_obj.__next__()
        print(x)
    except StopIteration:
        break

