import sys
def add_1(x):

    return x + 1
    
def main(argc, argv):

    x = int( 4)

    x = add_1(x);
    print("%d\n"%( x), end = "")
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
