##############################################
##          PiRadioApp version 1.0          ##
## https://github.com/PiRadioApp/PiRadioApp ##
##############################################

## INSTALL
To install run script INSTALL:
> sudo sh INSTALL.sh

## RUN
If application not working please run commands:
> sudo systemctl enable piradio.service
> sudo systemctl start piradio.service
Optional:
> sudo systemctl daemon-reload

To check status:
> sudo systemctl status piradio.service

## CHANGE SETTINGS
Installation dir: /opt/PiRadioApp
App settings you can easily change using flags 
in script: run.sh
in reference to documentation (docs) on github, or file: help.json
