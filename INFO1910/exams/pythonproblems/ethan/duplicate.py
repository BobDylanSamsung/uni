def find_duplicates(ls):
    found = []

    #check its a list
    if str(type(ls)) != "<class 'list'>":
        return -1

    #parse through list
    i = 0
    while i < len(ls):

        #check its an integer in the range
        if ls[i] <= 0 or str(type(ls[i])) != "<class 'int'>":
            return -1

        #check if its been seen before
        j = 0
        while j < len(found):
            if ls[i] == found[j]:
                #if it has return that number
                return ls[i]
            j += 1

        #otherwise put it in the numbers seen
        found.append(ls[i])

        i += 1


    #everything different return 0
    return 0


print(find_duplicates([1,2,3,4,3]))


print(find_duplicates([3,1,2,2]))


print(find_duplicates([1,2,3,4]))


print(find_duplicates([0,1,2,3]))