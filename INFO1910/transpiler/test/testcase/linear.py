import sys

def main(argc, argv):

    x = int( 7)

    x = linear_eq(             x);
    print("%d\n"%(            x), end = "")
    return                0
    
def linear_eq(x):

    return 3*x-1
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
