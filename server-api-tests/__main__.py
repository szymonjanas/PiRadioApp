import tests
import sys
import subprocess
import time

if __name__ == "__main__":

    onlyFlag = False
    buildFlag = False

    for arg in sys.argv:
        if arg == "--only" or arg == "-o":
            onlyFlag = True
        if arg == "--build" or arg == "-b":
            buildFlag = True

    if onlyFlag:
        tests.test()
    else:
        # build all dependencies
        if buildFlag:
            subprocess.call(['./build.sh'])
            print("\nEXECUTE ###############################################")

        # execute 
        pidEngine = subprocess.Popen(['build/PiRadioApp', '--only', '-na', '-col', '-db', 'database.json'])
        time.sleep(3)
        pidServer = subprocess.Popen(['build/server', '-col'])
        time.sleep(3)
        tests.test()

        pidEngine.terminate()
        pidServer.terminate()

        subprocess.call(['rm', 'piradio.app'])
