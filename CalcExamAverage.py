"""
------------------------------------------------------------------------
[program description]
input marks output weighted exam average
------------------------------------------------------------------------
Author: Tommy Le
ID:     200298530
Email:  lexx8530@mylaurier.ca
__updated__ = "2020-10-02"
------------------------------------------------------------------------
"""
#inputs
midterm_mark = int(input("Midterm Mark (%): "))
final_exam_mark = int(input("Final exam mark (%): "))

#calculations
weighted_exam = ((0.2 * midterm_mark) + (0.4 * final_exam_mark)) / (0.2 + 0.4)

#output
print()
print("Your weighted exam average is: {:.1f} %. The passing mark of the weighted exam average is 50%".format(weighted_exam))
