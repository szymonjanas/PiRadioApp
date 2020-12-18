import json
from termcolor import colored as col

debugFlag = False

__currnetClass__ = 0
__allClass__ = 0
__currnetCase__ = 0
__allCases__ = 0
__currentClassName__ = ""
__currnetCaseName__ = ""

def TestCheck(result : bool, message : str):
    global __currentClassName__, __currnetCase__, __currnetCaseName__
    if not result:
        print(__currentClassName__ + ": [   " + col("FAIL", "red") + "   ]" + " CASE " + str(__currnetCase__) + ": " + "  " + __currnetCaseName__ )
        raise Exception(__currnetCaseName__ + ": " + message)
    elif debugFlag:
        print(__currentClassName__ + ": [  " + col("PASS", "green") + "  ]" + " CASE " + str(__currnetCase__) + ": " + "  " + __currnetCaseName__ )

def __TestClass__():
    global __currentClassName__, __currnetClass__, __allClass__
    print("TestClass: " + __currentClassName__ + " " + str(__currnetClass__) + "/" + str(__allClass__))

def __TestClassSummary__():
    global __currentClassName__, __currnetCase__
    print("TestClass: " + __currentClassName__ + ": " + col("Test passed, ", "green") + "cases: " + str(__currnetCase__))
    print("-----------------------------------------------------")

def __TestSummary__():
    global __allClass__, __allCases__
    print("[  " + col("All tests passed", "green") + "  ]")
    print("    all tests: " + str(__allClass__))
    print("    all cases: " + str(__allCases__))

__register__ = []
def TestClass(testObject):
    __register__.append(testObject)

def __TestGetCasesFromClass__(testObject):
    tempTestMethods = dir(testObject().__class__)
    tempTestMethods.reverse()
    testMethods = []
    for method in tempTestMethods:
        if '__' not in method:
            testMethods.append(method)
    return testMethods

def __TestRun__(testObject):
    global __currnetCaseName__, __currentClassName__, __currnetCase__, __currnetClass__, __allCases__, __allClass__
    __currentClassName__ = testObject.__name__
    __currnetCase__ = 0
    __currnetClass__ += 1
    __TestClass__()
    testMethods = __TestGetCasesFromClass__(testObject)
    for method in testMethods:
        __currnetCase__ += 1
        __allCases__ += 1
        __currnetCaseName__ = method
        getattr(testObject(), method)()
    __TestClassSummary__()

def TestsRun():
    global __register__, __allClass__
    __allClass__ = len(__register__)

    for testObject in __register__:
        __TestRun__(testObject)
    __TestSummary__()

def TestRun(name : str):
    for testObject in __register__:
        if testObject.__name__ == name:
            __TestRun__(testObject)
            break

def TestCaseRun(testObjectName : str, caseName : str):
    global __currnetCaseName__, __currentClassName__
    for testObject in __register__:
        __currentClassName__ = testObject.__name__
        if testObjectName == "*":
            testMethods = __TestGetCasesFromClass__(testObject)
            for method in testMethods:
                if method == caseName:
                    __currnetCaseName__ = method
                    getattr(testObject(), method)()
        elif testObject.__name__ == testObjectName:
            testMethods = __TestGetCasesFromClass__(testObject)
            for method in testMethods:
                if method == caseName:
                    __currnetCaseName__ = method
                    getattr(testObject(), method)()
                    break

# @TestClass
# class SomeTestClass(object):
#     def caseFirst(self):
#         TestCheck(True, "thats test passed")
    
#     def caseSecond(self):
#         TestCheck(True, "failed beacuse i waneted to fail")

#     def caseThrid(self):
#         TestCheck(True, "failed beacuse i waneted to fail 2")

# @TestClass
# class SomeOtherClass(object):
#     def caseFirst(self):
#         TestCheck(True, "thats test passed")
    
#     def caseSecond(self):
#         TestCheck(True, "failed beacuse i waneted to fail")

#     def caseThrid(self):
#         TestCheck(True, "failed beacuse i waneted to fail 2")

# debugFlag = True
# TestsRun()
