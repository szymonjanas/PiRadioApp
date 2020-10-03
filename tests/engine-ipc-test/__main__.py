import test
import sys

if __name__ == "__main__":
    print("Start...")
    testsFlag = True
    for arg in sys.argv:
        if arg == "--debug":
            test.debugFlag = True
        if arg == "--ipc-debug":
            test.ipcFlag = True
        if arg == "--help" or arg == "-h":
            print("Help: [--debug] [--ipc-debug] [--help]")
            testsFlag = False
    if testsFlag:
        test.test()


