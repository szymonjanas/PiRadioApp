import test
import sys

if __name__ == "__main__":
    print("Test running...")
    testsFlag = True
    for arg in sys.argv:
        if arg == "--debug":
            test.debugFlag = True
        if arg == "--ipc-debug":
            test.ipcFlag = True
        if arg == "--help" or arg == "-h":
            print("Help: [--debug] [--ipc-debug] [--help]")
            testsFlag = False
        if arg == "--basic" or arg == "-b":
            test.basicFlag = True
    if testsFlag:
        test.test()
