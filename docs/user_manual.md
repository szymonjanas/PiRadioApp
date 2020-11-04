# User manual

## Install & Run
### piradio.deb
deb
change settings
<!-- TODO -->

### piradio.tar
1. Download and unpack tar. 
   ```Cpp
        tar xvf piradio.tar.gz
   ```
2. Change settings (set proper flags in reference to documentation or help file) in `run.sh` script if needed.
3. To install run:
   ```Cpp
        sudo sh INSTALL.sh
   ```
4. If everything went good, you can remove downloaded files.
   ```Cpp
        rm piradio.tar
        rm -r piradio 
   ```
### In every case 
- To turn on aplication in background type:
    ```Cpp
        sudo systemctl enable piradio.service
    ```
    To run application:
    ```Cpp
        sudo systemctl start piradio.service
    ```
    To check if application is running:
    ```Cpp
        sudo systemctl status piradio.service
    ```
    To reload daemon (could be required):
    ```Cpp
        sudo systemctl daemon-reload
    ```
- To change setting while running or because app not running.
    ```Cpp
        sudo systemctl stop piradio.service
    ```
    Change settings (flags) in `/opt/PiRadioApp/run.sh`.
    ```Cpp
        sudo systemctl start piradio.service
    ```
    Can be require to reload daemon.

## Change settings and avaliable options
<!-- TODO -->

## Manual install & Run, Compile from source
Install and run from deb package is recommended, because in manual way there can occur dependency problems.
If you still intrested in manual install go [developer manual](developer_manual.md), or [developer manual install](developer_manual_install.md).
