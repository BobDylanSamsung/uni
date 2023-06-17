numbers = [[1,2,[3]],4,5,[6,7],[[[8],9]],[[[[[[[[[[1],2],3],4],5],6],7]]]]]

def flatten(current, new = []):
    for i in current:
        if str(type(i)) == "<class 'list'>":
            print("this")
            new = flatten(i, new)
        else:
            print("taht")
            new.append(i)
    return new

new = flatten(numbers)

print(new)

