"""
------------------------------------------------------------------------
[program description]
input positive two-digit number output sum of two digit num.
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-10-02"
------------------------------------------------------------------------
"""
#input
num_n = int(input("Input a positive two digit number: "))

#Arrange
first_num = (num_n // 10)

second_num = (num_n % 10)

#calculation
sum_total = (first_num + second_num)

#output
print("The sum of the two digits is: {}".format(sum_total))