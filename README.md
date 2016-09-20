Perform elementwise unary, binary, and reduce operations on NumPy vectors in parallel using OpenMP.

REQUIREMENTS:  Python3, OpenMP (to use parallel capability)

USAGE:

operations.applyUnary(x,op,d):

    x  - a NumPy array of arbitrary dimensionality that is modified by an operation in place
    op - a string indicating the desired unary operation to perform
    d  - a double-valued parameter used in some operations

    Currently implemented unary operations are
  
        fill  - sets every element to d
        scale - multiplies every element to d
        shift - adds d to every element
        pow   - raises every element to the power d
        exp   - computes the exponential of every element
        log   - computes the logarithm of evert element
      

operations.applyBinary(x,y,op):

    x  - a NumPy array of arbitrary dimensionality
    y  - a NumPy array of arbitrary dimensionality, but the same number of elements as x
    op - a string indicating the desired binary operation to perform

    Currently implemented binary operations are

        add  - adds the array x to y, stores result in x
        sub  - subtracts the array y from x, stores result in x
        mult - multiplies the array x by y elementwise, stores result in x
        div  - divides the array x by y elementwise, stores the result in x


operations.reduce(x,op):

    x  - a NumPya array of arbitrary dimensionality
    op - a string indicating the desired reduction operation to perform     

    Currently implemented reduction operations are min, max, and sum
