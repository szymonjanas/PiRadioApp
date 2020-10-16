import testing
import test_engine_ipc
import test_server_api
import sys, time, subprocess, os

if __name__ == "__main__":
    print("Testing...")
    testEngineFlag = True
    testServerFlag = True
    runEngineFlag = True
    runServerFlag = True
    debugFlag = False
    basicFlag = False
    testsFlag = True
    for arg in sys.argv:
        if arg == "--debug":
            debugFlag = True
        if arg == "--ipc-debug":
            test_engine_ipc.ipcFlag = True
        if arg == "--basic":
            basicFlag = True
        if arg == "--test_engine" or arg == "-te":
            testEngineFlag = True
            testServerFlag = False
        if arg == "--test_server" or arg == "-ts":
            testEngineFlag = False
            testServerFlag = True
        if arg == "--off_engine" or arg == "-offe":
            runEngineFlag = False
        if arg == "--off_server" or arg == "-offs":
            runServerFlag = False
        if arg == "--off":
            runEngineFlag = False
            runServerFlag = False
        if arg == "--help" or arg == "-h":
            print("Help: [--debug] [--ipc-debug] [--help] [--basic] [--test_engine] [-te] [--test_server] [-ts] [--off_server] [-offs] [--off_engine] [-offe] [--off]")
            testsFlag = False

    if testsFlag:
        pidEngine = None
        addressTestEngine = 'tcp://127.0.0.1:5010'
        if runEngineFlag:
            pidEngine = subprocess.Popen(['build/PiRadioApp', '--only', '-na', '-col', '-db', 'test-database.json', '--debug', '-ica', addressTestEngine])
        time.sleep(3)
        if testEngineFlag:
            test_engine_ipc.debugFlag =debugFlag
            test_engine_ipc.connect(addressTestEngine)
            test_engine_ipc.test.start()
        if pidEngine != None:
            test_engine_ipc.disconnect(addressTestEngine)
            pidEngine.terminate()
            pidEngine.wait()
            pidEngine = None
        time.sleep(2)
# ANCHOR TU działa albo dla pierwszego albo dla drugiego 
# może warto przetestować dla ipc
        pidServer = None
        if testServerFlag:
            if runEngineFlag:
                pidEngine = subprocess.Popen(['build/PiRadioApp', '--only', '-na', '-col', '-db', 'test-database.json', '--debug', '-ica', 'tcp://127.0.0.1:5019'])
            time.sleep(2)
            if runServerFlag:
                pidServer = subprocess.Popen(['build/server', '-col', '--debug', '-ica', 'tcp://127.0.0.1:5019'])
            time.sleep(2)

            if testServerFlag:
                test_server_api.test.start()

        if pidServer != None:
            pidServer.terminate()
        if pidEngine != None:
            pidEngine.terminate()
