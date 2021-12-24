"""
-------------------------------------------------------
[program description]
Returns list of food objects given certain conditions
-------------------------------------------------------
Author:  Tommy Le
ID:      200298530
Email:   lexx8530@mylaurier.ca
__updated__ = "2021-01-17"
-------------------------------------------------------
"""
# Imports
from Food_utilities import read_foods, food_search
# open file and read
file_variable = open("foods.txt", "r")
# call read_foods
foods = read_foods(file_variable)
# input
origin = int(input("Origin: "))
max_cals = int(input("Max Calories: "))
is_veg = input("Vegetarian(True/False): ")
# call food_search
results = food_search(foods, origin, max_cals, is_veg)
