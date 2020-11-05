echo "Installing..."
echo "sudo required!"
echo ""

# Installing service for auto run application in background
# to check status type: sudo systemctl status piradio.service
# to enable: sudo systemctl enable piradio.service
# to stop: sudo systemctl stop piradio.service
# can be daemon reload required: sudo systemctl daemon-reload
# more: systemctl --help

sudo mv -f PiRadioApp/piradio.service /etc/systemd/system

# To link library
sudo mv -f PiRadioApp/piradio.conf /etc/ld.so.conf.d

# Addictional gst plugins for service all streams
sudo apt install gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-ugly

# Installing app folder in /opt (optional) directory, due to linux directory assignments.
mv PiRadioApp /opt

echo "Done. If everythink went good, you can remove this folder!"
