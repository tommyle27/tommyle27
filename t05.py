"""
------------------------------------------------------------------------
[program description]
Assignment 01, Q5
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-09-17"
------------------------------------------------------------------------
"""
#principal amount
p = 6000.0
#annual rate of interest(decimal)
r = 0.03
#number of years the amount is deposited/borrowed
t = 12.0
#number of times the interest is compounded per year
n = 24.0
#Calculating compound interest A= amount of money accumulated after t years
A = p*(1+r/n)**(n*t)
#print balance after 10 years
print("After twelve years your balance is, {:.2f}".format(A))