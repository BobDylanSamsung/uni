from sys import argv, exit

def tennanachi(n):
    #TODO: return the nth tennanachi number
    return 0

if __name__=='__main__':
    if len(argv) != 2:
        print('Usage: {} <n>'.format(argv[0]))
        exit(1)
    print(tennanachi(int(argv[1])))
