import sys
def main(argc, argv):

    x = int( 4)

    y = str( 'f')

    z = float( 0.618)

    print("%d\t%s\t%f\n"%( x,y,z), end = "")
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
