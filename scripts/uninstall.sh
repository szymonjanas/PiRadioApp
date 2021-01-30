echo "Uninstall application"

rm -fv /etc/systemd/system/piradio.service

rm -fv /etc/ld.so.conf.d/piradio.conf

rm -rfv /opt/PiRadioApp
