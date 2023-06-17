import sys
def main(argc, argv):

    asdf = int( 20)

    while(asdf != 10):
        asdf = asdf - 1
        x = int( asdf/4)

        print("x i %d"%(x), end = "")
        print("asdf is %d\n"%( asdf), end = "")
        
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
