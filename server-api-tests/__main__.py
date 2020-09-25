import tests
import sys
import subprocess
import time

if __name__ == "__main__":

    onlyFlag = False

    for arg in sys.argv:
        if arg == "--only" or arg == "-o":
            onlyFlag = True

    if onlyFlag:
        tests.test()
    else:
        pidEngine = subprocess.Popen(['build/PiRadioApp', '--only', '-na', '-col', '-db', 'database.json'])
        time.sleep(3)
        pidServer = subprocess.Popen(['build/server', '-col'])
        time.sleep(3)
        tests.test()
