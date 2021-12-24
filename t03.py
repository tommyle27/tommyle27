"""
-------------------------------------------------------
[program description]
Calc average calories of specific origin group
-------------------------------------------------------
Author:  Tommy Le
ID:      200298530
Email:   lexx8530@mylaurier.ca
__updated__ = "2021-01-17"
-------------------------------------------------------
"""
# Imports
from Food_utilities import calories_by_origin, read_foods


file_variable = open("foods.txt", "r")
foods = read_foods(file_variable)
origin = input("Origin: ")
if origin == "Canadian":
    origin = 0
elif origin == "Chinese":
    origin = 1
elif origin == "Indian":
    origin = 2
elif origin == "Ethiopian":
    origin = 3
elif origin == "Mexican":
    origin = 4
elif origin == "Greek":
    origin = 5
elif origin == "Japanese":
    origin = 6
elif origin == "Italian":
    origin = 7
elif origin == "American":
    origin = 8
elif origin == "Scottish":
    origin = 9
elif origin == "New Zealand":
    origin = 10
elif origin == "English":
    origin = 11

a = calories_by_origin(foods, origin)
print(a)
