echo "Uninstall application"
echo "sudo required!"


echo "Stopping piradio.service!"
systemctl stop piradio.service

echo "Remove piradio.service"
rm -fv /etc/systemd/system/piradio.service

echo "remove piradio.conf"
rm -fv /etc/ld.so.conf.d/piradio.conf

echo "remove PiRadioApp"
rm -rfv /opt/PiRadioApp

echo "Please restart daemon with command: sudo systemctl daemon-reload"
echo "or stop service with"
