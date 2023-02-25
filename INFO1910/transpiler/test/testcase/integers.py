import sys
def main(argc, argv):

    a = int(2)
    b = int(3)
    c = int( 4)
    d = int(0)

    print("%d\t%d\t%d\t%d\n"%( a,b,c,d), end = "")
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
