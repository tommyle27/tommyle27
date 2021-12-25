"""
------------------------------------------------------------------------
[program description]
divide num balloons evenly among children
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-10-02"
------------------------------------------------------------------------
"""
#input
num_balloons = int(input("Number of balloons: "))
num_children = int(input("Number of children: ")) 

#calculations
balloons_per_child = (num_balloons // num_children)
balloons_remain = (num_balloons % num_children)

#output
print()

print("Each child will receive {:.0f} balloons".format(balloons_per_child))
print("Balloons that will not be distributed: {}".format(balloons_remain))