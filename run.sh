PiRadio=/usr/bin/piradio

$PiRadio/PiRadioApp \ 
    -res $PiRadio/resources \
    -rsc $PiRadio/server \
    -db $PiRadio/database/radio-stations.json \
    -sha 127.0.0.1:7983
