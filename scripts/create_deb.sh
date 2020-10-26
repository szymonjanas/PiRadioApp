echo "Creating deb package..."

VER=v0.6

sh build.sh
cd ..

echo "Assembly deb package..."
echo ""
mkdir -v -p linuxconfig/DEBIAN
mkdir -v -p linuxconfig/usr/bin/piradio
cp -v control linuxconfig/DEBIAN
cp -v help.json linuxconfig/usr/bin/piradio
cp -v -r server/resources linuxconfig/usr/bin/piradio

cd build
cp -v PiRadioApp ../linuxconfig/usr/bin/piradio
cp -v libPiRadioAppEngineLib.so ../linuxconfig/usr/bin/piradio
cp -v server ../linuxconfig/usr/bin/piradio
cp -v run.sh ../linuxconfig/usr/bin/piradio
cd ..

mkdir -v -p linuxconfig/etc/systemd/system
cp -v piradio.service linuxconfig/etc/systemd/system

dpkg-deb -v --build linuxconfig
mkdir -v out
mv -v linuxconfig.deb out/PiRadioApp-$VER.deb
echo ""
echo "Created! You can find out deb package in directory '/out' "
echo ""
