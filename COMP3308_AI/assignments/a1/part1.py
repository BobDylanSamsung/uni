def task1(key, filename, indicator):
    n = len(key)
    keys = [key[i:i + 2] for i in range(0, n, 2)]
    f = open(filename, "r")
    filestring = f.read()
    letters = [*filestring]
    f.close()
    if indicator == 'd':
        keys.reverse()

    for i in range(len(letters)):
        for k in keys:
            if letters[i] == k[0]:
                letters[i] = k[1]
            elif letters[i] == k[0].lower():
                letters[i] = k[1].lower()
            elif letters[i] == k[1]:
                letters[i] = k[0]
            elif letters[i] == k[1].lower():
                letters[i] = k[0].lower()

    return ''.join(str(l) for l in letters)


if __name__ == '__main__':
    # Example function calls below, you can add your own to test the task1 function
    print(task1('AE', 'spain.txt', 'd'))
    print(task1('VFSC', 'ai.txt', 'd'))
    print(task1('ABBC', 'cabs_plain.txt', 'e'))
