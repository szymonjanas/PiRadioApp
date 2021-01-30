echo "Uninstall application"
echo "sudo required!"

echo "INFO stopping piradio.service!"
systemctl stop piradio.service

echo "INFO remove piradio.service"
rm -fv /etc/systemd/system/piradio.service

echo "INFO remove piradio.conf"
rm -fv /etc/ld.so.conf.d/piradio.conf

echo "INFO remove PiRadioApp"
rm -rfv /opt/PiRadioApp
