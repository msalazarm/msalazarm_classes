#Name:Marco Salazar, Date: 9/27/2020
#Purpose: to compare Python with numpy in gaussian elimination to other programming languages running times.
#No Inputs, instead it calls all the gaussian elimination in order.
#Outputs in CSV format

import numpy as np
import math
import time
import timeit

#https://numpy.org/doc/stable/reference/arrays.nditer.html
#https://stackoverflow.com/questions/52864988/compare-the-result-of-gaussian-elimination-with-the-output-of-numpy-linalg-solve
# creates random array and computes the gaussian elimination of it.
def gaus(length):
    array = np.random.rand(length,length)
    with np.nditer(array, op_flags=['readwrite']) as it:
        for x in it:
            x[...] = math.floor(x*999)+1

    brray = np.random.rand(length,1)
    with np.nditer(array, op_flags=['readwrite']) as it:
        for x in it:
            x[...] = math.floor(x*999)+1

    start_time = timeit.default_timer()*1000000000
    x = np.linalg.solve(array, brray)
    print("%s," % (timeit.default_timer()*1000000000- start_time))

# Do all of the 5 tries for each of the 5 sizes.
gaus(250)
gaus(250)
gaus(250)
gaus(250)
gaus(250)

gaus(500)
gaus(500)
gaus(500)
gaus(500)
gaus(500)

gaus(1000)
gaus(1000)
gaus(1000)
gaus(1000)
gaus(1000)

gaus(1500)
gaus(1500)
gaus(1500)
gaus(1500)
gaus(1500)

gaus(2000)
gaus(2000)
gaus(2000)
gaus(2000)
gaus(2000)