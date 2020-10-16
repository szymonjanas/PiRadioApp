import json
from termcolor import colored as col

class TestClass:
    def __init__(self):
        self.debugFlag = False

        self.basicFlag = False
        self.testNumber = 1
        self.caseNumber = 1
        self.allCase = 1
        self.testsList = []

    def start(self):
        for func in self.testsList:
            if not self.basicFlag:
                print()
                print("TEST " + str(self.testNumber) + " RUN... " + func.__name__)
                print("-----------------------------------------------------")
            func()
            print("[  " + col("TEST", "green") + "  ]" + " " + \
            "TEST " + str(self.testNumber) +":   ALL CASE " + col("PASS", "green") + \
            " " + str(self.caseNumber-1) + "/" + str(self.caseNumber-1) + \
            ", all: " + str(self.allCase-1) + " | " + str(self.testNumber) + "  " + func.__name__)
            self.testNumber += 1
            self.caseNumber = 1

    def check(self, funcName : str, state : bool, message : str):
        if state:
            if not self.basicFlag:
                print("[  " + col("PASS", "green") + "  ]" + " CASE " + str(self.caseNumber) + ": " + "  " + funcName )
        else:
            if not self.basicFlag:
                print("[   " + col("FAIL", "red") + "   ]" + " CASE " + str(self.caseNumber) + ": " + "  " + funcName )
            raise Exception(funcName + ": " + message)
        self.caseNumber += 1
        self.allCase += 1

    def add(self, test_case):
        self.testsList.append(test_case)
