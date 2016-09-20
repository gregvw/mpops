import operations as ops
import numpy as np

if __name__ == "__main__":

    n = 4
    t = np.linspace(0,1,2*n)
    s = np.linspace(0,1,n)
    x = np.outer(t,s)   

    w = t;    
    y = np.random.rand(n)
    z = np.random.rand(n)

    print(y)
    print(z)
    ops.applyBinary(y,z,"add")
    print(y)

    print(w)
    ops.applyUnary(w,"exp")
    ops.applyUnary(w,"pow",2.0)
    print(w)

    print(ops.reduce(np.ones(n),"sum"))
