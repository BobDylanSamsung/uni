import sys
def main(argc, argv):

    asdf = int( 20)

    while(asdf > 10):
        asdf = asdf - 1
        print("hello %d\n"%( asdf), end = "")
        
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
