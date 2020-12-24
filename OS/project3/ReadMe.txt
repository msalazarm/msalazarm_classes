Marco Salazar and Catalina Sanchez-Maes on 11/20/2020
for Project 3 of CS 471 Operating Systems.

Description:
This program will print out the order that the monkeys leave in the form of L/R#: (#, #, #)
          Where L or R indicate whether the monkey is going left to right, or right to left respectively.
          Where the first number indicates which monkey it is, and the array of numbers indicates
          What monkeys were on the rope the moment before it left. If working correctly, the first
          number should be equal to the lowest nonzero number in the array next to it.
Note: The array position of the numbers in the array do not indicate the postion of the baboons on the rope. Only the values do.


to compile simply use: 
 gcc project3.c -lpthread -lrt -o project3

to run use:
 ./project3 order.txt 10

where order.txt is your text file that holds the order of the monkeys in the form:
L,R,L,R,R

and 10 or any number you choose is the number of seconds that each monkey takes to cross.