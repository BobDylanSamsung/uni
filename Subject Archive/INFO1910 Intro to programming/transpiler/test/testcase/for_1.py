import sys
def main(argc, argv):

    x = 0-1
    while x < 10:
        x += 1
        if not x < 10: break
        print("hello %d\n"%( x), end = "")
        
    return 0
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
