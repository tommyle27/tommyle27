"""
------------------------------------------------------------------------
[program description]
Functions
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-10-19"
------------------------------------------------------------------------
"""
#task 01 function
from ast import Num
def falling_distance(sec):
    """
    -------------------------------------------------------
    Calculate distance an object falls in a specific period of time
    Use: sec = falling_distance(sec)
    -------------------------------------------------------
    Parameters: 
    sec - number of seconds given (int>=0)
    return:
    d - falling_distance(sec) (int > 0)
    
    -------------------------------------------------------
    """
    #calculations
    g = 9.8
    d = (1/2) * g * (sec**2)
    #return
    return d

#task 02 function
def calorie_calculator(fat_calories, carb_calories):
    """
    -------------------------------------------------------
    calculate fat and carb calories and total calories
    use: fat_calories, carb_calories, total_calories = calorie_calculator(fat_calories, carb_calories)
    -------------------------------------------------------
    Parameters: 
    fat_calories - number of fat calories consumed(int > 0)
    carb calories - number of carb calories consumed(int > 0)
    return:
    fats - number of fat calories(int>=0)
    carbs - number of carb calories(int>=0)
    total - sum of fat and carb calories(int)
    
    -------------------------------------------------------
    """
    #calculations
    fats = fat_calories * 9
    carbs =  carb_calories * 4
    total = fats + carbs
    #return
    return fats, carbs, total
    
#task 03 function
def convert_date(date_int):
    """
    -------------------------------------------------------
    converts date_int into days, month, and year
    use: day, month, year = convert_date(date_int)
    -------------------------------------------------------
    Parameters: 
    date_int - (int > 0)
    return:
    day: the day in the month in date_int (int >= 0)
    month: the month in date_int (int >= 0)
    year: the year in date_int (int >= 0)
    
    -------------------------------------------------------
    """
    #calculation
    month = (date_int//1000000)

    year = (date_int % 10000)

    find_day = (date_int//10000)
    day = (find_day%100)
    #return
    return day, month, year

#task 04
def convert_sec(num_sec):
    """
    -------------------------------------------------------
    converts num_sec into days, hours, minutes, and seconds
    use: days, hours, minutes, seconds = convert_sec(num_sec)
    -------------------------------------------------------
    Preconditions: 
    nu,_sec - (int > 0)
    return:
    days: number of days in num_sec (int >= 0)
    hours: number of hours in num_sec (int >= 0)
    minutes: number of minutes in num_sec (int >= 0)
    seconds: number of seconds in num_sec (int >= 0)
    
    -------------------------------------------------------
    """
    #calculations
    days = num_sec // (24 * 3600)

    num_sec = num_sec % (24 * 3600)
    hours = num_sec // 3600

    num_sec %= 3600
    minutes = num_sec // 60

    num_sec %= 60
    seconds = num_sec
    #return
    return days, hours, minutes, seconds

#task 05
import random
def math_quiz():
    """
    -------------------------------------------------------
    allows user to enter answer and displays user's answer along with the correct answer
    -------------------------------------------------------
    """ 
    #quiz
    for x in range(1):
        x = random.randint(1,999)
    for y in range(1):
        y = random.randint(1,999)
    print (" ", x)
    print ("+", y)
    print("-----")
    #variable/correct answer
    correct_ans = x + y
    #input answer
    answer = int(input("  "))
    #output
    print("Your answer: {}, it should be: {}".format(answer, correct_ans))  
   

    