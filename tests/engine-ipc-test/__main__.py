import test
import sys, time, subprocess

if __name__ == "__main__":
    print("Test running...")
    testsFlag = True
    engineFlag = False

    for arg in sys.argv:
        if arg == "--debug":
            test.debugFlag = True
        if arg == "--ipc-debug":
            test.ipcFlag = True
        if arg == "--help" or arg == "-h":
            print("Help: [--debug] [--ipc-debug] [--help] [--basic] [--engine]")
            testsFlag = False
        if arg == "--basic":
            test.basicFlag = True
        if arg == "--engine" or arg == "-e":
            engineFlag = True

    if testsFlag:

        if engineFlag:
            pidEngine = subprocess.Popen(['build/PiRadioApp', '--only', '-na', '-col', '-db', 'test-database.json'])
            time.sleep(3)
        
        test.test()

        if engineFlag:
            pidEngine.terminate()
            subprocess.call(['rm', 'piradio.app']) 
