import sys
def main(argc, argv):

    e = float( 2.718)

    x = float( 3.1415)

    print("%f, %f\t %f\n"%( e, x, e+x), end = "")
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
