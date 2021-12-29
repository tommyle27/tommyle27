"""
-------------------------------------------------------
[program description]
-------------------------------------------------------
Author:  Tommy Le
ID:      200298530
Email:   lexx8530@mylaurier.ca
__updated__ = "2021-02-06"
-------------------------------------------------------
"""
# Imports
from Stack_array import Stack
# Constants


def stack_split_alt(source):
    """
    -------------------------------------------------------
    Splits the source stack into separate target stacks.
    When finished source stack is empty. Values are
    pushed alternately onto the returned target stacks.
    Use: target1, target2 = stack_split_alt(source)
    -------------------------------------------------------
    Parameters:
        source - the stack to split into two parts (Stack)
    Returns:
        target1 - contains alternating values from source (Stack)
        target2 - contains other alternating values from source (Stack)
    -------------------------------------------------------
    """
    target1 = Stack()
    target2 = Stack()
    test = True

    for i in range(0, source._capacity):
        if test:
            value = source.pop()
            target1.push(value)
            test = False
        else:
            value = source.pop()
            target2.push(value)
            test = True

    return target1, target2


def stack_combine(source1, source2):
    """
    -------------------------------------------------------
    Combines two given Stacks into a target stack.
    When finished, the contents of source1 and source2 are interlaced
    into target and source1 and source2 are empty.
    Use: target = stack_combine(source1, source2)
    -------------------------------------------------------
    Parameters:
        source1 - a stack (Stack)
        source2 - another stack (Stack)
    Returns:
        target - the contents of the source1 and source2
            are interlaced into target (Stack)
    -------------------------------------------------------
    """
    target = Stack()
    while not (source1.isEmpty() or source2.isEmpty()):
        if not source1.isEmpty():
            value = source1.pop()
            target.push(value)
        if not source2.isEmpty():
            value = source2.pop()
            target.push(value)

    return target


# Constants
OPERATORS = "+-*/"


def postfix(string):
    """
    -------------------------------------------------------
    Evaluates a postfix expression.
    Use: answer = postfix(string)
    -------------------------------------------------------
    Parameters:
        string - the postfix string to evaluate (str)
    Returns:
        answer - the result of evaluating string (float)
    -------------------------------------------------------
    """
    target = Stack()
    list1 = string.split()
    print(list1)
    size = len(list1)
    n = 0
    while n < size:
        if list1[n].isdigit():
            target.push(list1[n])
            print(list1[n])
        elif list1[n] == "+":
            num1 = target.pop()
            num2 = target.pop()
            num3 = float(num1) + float(num2)
            target.push(num3)
            print(num3)
        elif list1[n] == "-":
            num1 = target.pop()
            num2 = target.pop()
            num3 = float(num2) - float(num1)
            target.push(num3)
            print(num3)
        elif list1[n] == "*":
            num1 = target.pop()
            num2 = target.pop()
            num3 = float(num1) * float(num2)
            target.push(num3)
            print(num3)
        elif list1[n] == "/":
            num1 = target.pop()
            num2 = target.pop()
            num3 = float(num2) / float(num1)
            target.push(num3)
            print(num3)
        n += 1
    answer = target.pop()
    return answer


def stack_maze(maze):
    """
    -------------------------------------------------------
    Solves a maze using Stack.
    Use: path = stack_maze(maze)
    -------------------------------------------------------
    Parameters:
        maze - dictionary of points in a maze, where each point
            represents a corridor end or a branch. Dictionary
            keys are the name of the point followed by a list of
            branches, if any. First point is named 'Start', exit
            is named 'X' (dict)
    Returns:
        points - list of points visited before the exit is reached,
            None if there is no exit (list of str)
    -------------------------------------------------------
    """
    points = Stack()
    value = Stack()
    solution = Stack()

    while len(maze) > 0:
        points.push(value.peek())
        if value.peek() == "X":
            for i in range(0, points._capacity):
                solution.push(points(i))
        if value.isEmpty():
            solution.pop()
            maze.pop()
            value = maze[key]
        else:
            for i in range(points._capacity):
                if value != [i]:
                    value.peek()

    return points
