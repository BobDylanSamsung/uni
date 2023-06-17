import sys

def quadratic_eq(num):

    num = linear_eq(num);
    y = float( (num*num +2*num -3.7)/ 2.9)

    return y
    
def main(argc, argv):

    x = float( quadratic_eq(4))

    print("%f\n"%( x), end = "")
    return 0
    
def linear_eq(s):

    return 4*s - 11
    
CALLMAINFUNCTIONVAR = main(len(sys.argv), sys.argv)
