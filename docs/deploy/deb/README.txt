##############################################
##          PiRadioApp version 1.0          ##
## https://github.com/PiRadioApp/PiRadioApp ##
##############################################

## Dependencies
to make sure every format will be working install:
> sudo apt install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-ugly

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
After changing settings service reload required:
> sudo systemctl reload piradio.service
> sudo systemctl daemon-reload
