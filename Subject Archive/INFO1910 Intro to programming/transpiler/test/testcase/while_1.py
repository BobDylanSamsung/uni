import sys
def main(argc, argv):

    x = int( 0)

    while(x<10)     :
        x = x + 1
        print("%d\n"%( x), end = "")
        
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
