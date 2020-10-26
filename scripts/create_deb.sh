echo "Creating deb package..."

sh build.sh
cd ..

echo "Assembly deb package..."
echo ""
mkdir -v -p linuxconfig/DEBIAN
cp -v control linuxconfig/DEBIAN
mkdir -v -p linuxconfig/usr/bin/piradio
cd -v build
cp -v PiRadioApp ../linuxconfig/usr/bin/piradio
cp -v libPiRadioAppEngineLib.so ../linuxconfig/usr/bin/piradio
cp -v server ../linuxconfig/usr/bin/piradio
cd -v ..
cp -v help.json linuxconfig/usr/bin/piradio
cp -v -r server/resources linuxconfig/usr/bin/piradio

dpkg-deb -v --build linuxconfig
mkdir -v out
mv -v linuxconfig.deb out/PiRadioApp-1.0.deb
echo ""
echo "Created! You can find out deb package in directory '/out' "
echo ""