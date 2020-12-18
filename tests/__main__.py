from testing import *
from test_server_api import *
import sys, time, subprocess, os

if __name__ == "__main__":
    print("Testing...")
    debugFlag = False
    runAppFlag = True
    for arg in sys.argv:
        if arg == "--debug":
            debugFlag = True
        if arg == "--no-run-app":
            runAppFlag = False

    pidEngine = None
    pidServer = None
    if runAppFlag:
        pidEngine = subprocess.Popen(['build/PiRadioApp', '-na', '--test', '-col', '-db', 'test-database.json', '--debug', '-ica', 'tcp://127.0.0.1:5555'])
        time.sleep(2)
        pidServer = subprocess.Popen(['build/server', '-ica', 'tcp://127.0.0.1:5555'])
        time.sleep(2)

    TestsRun()

    if pidEngine != None:
        pidEngine.terminate()
    if pidServer != None:
        pidServer.terminate()
