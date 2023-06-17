def rec_hailstone(n, ls):
    ls.append(n)
    if n == 1:
        return ls
    elif n%2 == 0:
        n = rec_hailstone(int(n/2), ls)
    else:
        n = rec_hailstone(n*3 + 1, ls)

    return ls

# Python program for implementation of Bubble Sort 
def bubbleSort(arr): 
    n = len(arr) 
  
    # Traverse through all array elements 
    for i in range(n): 
  
        # Last i elements are already in place 
        for j in range(0, n-i-1): 
  
            # traverse the array from 0 to n-i-1 
            # Swap if the element found is greater 
            # than the next element 
            if arr[j][1] > arr[j+1][1] : 
                arr[j], arr[j+1] = arr[j+1], arr[j]

i = 1
numbers = []
while i <= 1000:
    result = len(rec_hailstone(i, []))
    numbers.append([i, result])
    # print("i is: %d\t length is: %d"%(i, len(rec_hailstone(i, numbers))))
    i = i+1

bubbleSort(numbers)



for i, val in enumerate(numbers):
    print("i is: %d\t length is: %d"%(i, val[1]))