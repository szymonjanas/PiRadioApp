echo "Creating deb package..."

VER=v1.0

sh build.sh
cd ..

echo "Assembly deb package..."
echo ""
mkdir -v -p deploy/deb/piradio/DEBIAN
cp -v scripts/helpers/deb/control deploy/deb/piradio/DEBIAN

mkdir -v -p deploy/deb/piradio/opt/PiRadioApp
cp -v help.json deploy/deb/piradio/opt/PiRadioApp
cp -v -r server/resources deploy/deb/piradio/opt/PiRadioApp
cp -v -R example-database.json deploy/deb/piradio/opt/PiRadioApp/radio-database.json
cp -v scripts/helpers/run.sh deploy/deb/piradio/opt/PiRadioApp

cd build
cp -v PiRadioApp ../deploy/deb/piradio/opt/PiRadioApp
cp -v libPiRadioAppEngineLib.so ../deploy/deb/piradio/opt/PiRadioApp
cp -v server ../deploy/deb/piradio/opt/PiRadioApp
cd ..
cp -v scripts/uninstall.sh deploy/deb/piradio/opt/PiRadioApp

mkdir -v -p deploy/deb/piradio/etc/systemd/system
cp -v scripts/helpers/piradio.service deploy/deb/piradio/etc/systemd/system
mkdir -v -p deploy/deb/piradio/etc/ld.so.conf.d
cp -v scripts/helpers/piradio.conf deploy/deb/piradio/etc/ld.so.conf.d
cp -v docs/deploy/deb/README.txt deploy/deb/piradio/PiRadioApp

cd deploy/deb
dpkg-deb -v --build piradio
mv -v piradio.deb PiRadioApp-$VER.deb
echo ""
echo "Created! You can find out deb package in directory '/deploy' "
echo ""
