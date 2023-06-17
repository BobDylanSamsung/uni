def flatten(x, final = []):
    for item in x:
        print(item)
        #print(type(item))
        
        if type(item) is list:
            print("Run1")
            final = flatten(item, final)
        else:
            print("Run2")
            final.append(item)


x = [1,2,[2,3],4,[5],[6,[7,8]]]

flatten(x)