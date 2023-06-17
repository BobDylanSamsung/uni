import sys
def main(argc, argv):

    x = int( 123)
    y = int( 456)

    print("%d, %d\n"%( x, y), end = "")
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
