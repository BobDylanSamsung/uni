import sys

def main(argc, argv):

    x = int( 5)

    x = add_2(x);
    print("%d\n"%( x), end = "")
    return 0
    
def add_2(x):

    x = x + 2
    return x
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
