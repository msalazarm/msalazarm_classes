#Name:Marco Salazar, Date: 9/27/2020
#Purpose: to compare Python without numpy in gaussian elimination to other programming languages running times.
#No Inputs, instead it calls all the gaussian elimination in order.
#Outputs in CSV format

import math
import time
import timeit
import random

#https://learnche.org/3E4/Assignment_2_-_2010_-_Solution/Bonus_question with edits
def forward_elimination(A, b, n):
    """
    Calculates the forward part of Gaussian elimination.
    """
    for row in range(0, n-1):
        for i in range(row+1, n):
            factor = A[i][row] / A[row][row]
            for j in range(row, n):
                A[i][j] = A[i][j] - factor * A[row][j]

            b[i] = b[i] - factor * b[row]
    return A, b

def back_substitution(a, b, n):
    """"
    Does back substitution, returns the Gauss result.
    """
    x = [0 for j in range(n)]
    x[n-1] = b[n-1] / a[n-1][ n-1]
    for row in range(n-2, -1, -1):
        sums = b[row]
        for j in range(row+1, n):
            sums = sums - a[row][j] * x[j]
        x[row] = sums / a[row][row]
    return x

def gauss(A, b):
    """
    This function performs Gauss elimination without pivoting.
    """
    n = len(A[0])

    A, b = forward_elimination(A, b, n)
    return back_substitution(A, b, n)


def gaus(length):
    array = [[math.floor(random.random()*999)+1 for i in range(length)] for j in range(length)]
    brray = [math.floor(random.random()*999)+1 for j in range(length)]

    start_time = timeit.default_timer()*1000000000
    gauss(array, brray)
    print("%s," % (timeit.default_timer()*1000000000- start_time))

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