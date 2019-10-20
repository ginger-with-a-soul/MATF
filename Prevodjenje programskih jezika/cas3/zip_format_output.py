#! /usr/bin/python3
import sys

questions = ["name", "surname", "POB"]
answers = ["Dimitrije", "Stankov", "VA"]

for a, b in zip(questions, answers):
    print("Your {0}: Mine {0} is {1:10}".format(a, b))

for a, b in zip(questions, answers):
    print("Your %s: Mine %s is %5s"%(a, a, b))