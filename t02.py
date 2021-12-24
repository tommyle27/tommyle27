"""
-------------------------------------------------------
[program description]
calc average calories
-------------------------------------------------------
Author:  Tommy Le
ID:      200298530
Email:   lexx8530@mylaurier.ca
__updated__ = "2021-01-17"
-------------------------------------------------------
"""
# Imports
from Food_utilities import average_calories, read_foods

file_variable = open("foods.txt", "r")
foods = read_foods(file_variable)
avg = average_calories(foods)
print(avg)
