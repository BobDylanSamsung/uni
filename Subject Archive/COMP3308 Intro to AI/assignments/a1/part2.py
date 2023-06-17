import itertools

def decode(letters_to_swap, string_to_decode):
    k = letters_to_swap
    letters = [*string_to_decode]

    num_swaps = 0
    for i in range(len(letters)):
        if letters[i] == k[0].upper():
            letters[i] = k[1].upper()
            num_swaps += 1
        elif letters[i] == k[0].lower():
            letters[i] = k[1].lower()
            num_swaps += 1
        elif letters[i] == k[1].upper():
            letters[i] = k[0].upper()
            num_swaps += 1
        elif letters[i] == k[1].lower():
            letters[i] = k[0].lower()
            num_swaps += 1

    return ''.join(str(l) for l in letters), num_swaps


def task2(filename, letters):
    letters = set([*letters])
    keys = sorted(
        itertools.combinations(letters, 2),
        key=lambda x:
        (x[0], x[1])
        if x[0] < x[1]
        else (x[1], x[0])
    )
    results = []

    with open(filename, "r") as f:
        string_to_encode = f.read()

    for k in keys:
        res, n = decode(k, string_to_encode)
        if n > 0:
            results.append(res)

    return_str = str(len(results))
    if len(results):
        return_str += "\n"
    return_str += "\n\n".join(results)
    return return_str


if __name__ == '__main__':
    # Example function calls below, you can add your own to test the task2 function
    print(task2('spain.txt', 'ABE'))
    print(task2('ai.txt', 'XZ'))
    print(task2('cabs.txt', 'ABZD'))
