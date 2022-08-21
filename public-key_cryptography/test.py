import math
import numpy

def f(x, q = 256):
    return ((x << 12) % 333 + 1) % q

for x in range(256):
    print("%5d %3d"%(x, f(x)))


