"""
------------------------------------------------------------------------
[program description]
Input date MMDDYYYY, output DD/MM/YYYY
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-09-30"
------------------------------------------------------------------------
"""
#input date
date = int(input("Enter a date in the format MMDDYYYY: "))

#calculation
month = (date//1000000)

year = (date % 10000)

find_day = (date//10000)
day = (find_day%100)

#print output
print("{:02d}/{:02d}/{}".format(day,month,year))
