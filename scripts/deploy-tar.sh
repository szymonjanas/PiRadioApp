echo "Creating simple app deploy..."

VER=v1.0

sh build.sh
cd ..

echo "Assembly simple app deploy..."
echo ""
mkdir -v -p deploy/tar/piradio/PiRadioApp
cp -v help.json deploy/tar/piradio/PiRadioApp
cp -v -r server/resources deploy/tar/piradio/PiRadioApp
cp -v -R example-database.json deploy/tar/piradio/PiRadioApp/radio-database.json

cd build
cp -v PiRadioApp ../deploy/tar/piradio/PiRadioApp
cp -v libPiRadioAppEngineLib.so ../deploy/tar/piradio/PiRadioApp
cp -v server ../deploy/tar/piradio/PiRadioApp
cd ..
cp -v scripts/helpers/run.sh deploy/tar/piradio/PiRadioApp
cp -v scripts/helpers/piradio.service deploy/tar/piradio/PiRadioApp
cp -v scripts/helpers/piradio.conf deploy/tar/piradio/PiRadioApp
cp -v scripts/helpers/tar/INSTALL.sh deploy/tar/piradio
cp -v docs/deploy/tar/README.txt deploy/tar/piradio/PiRadioApp
cp -v scripts/uninstall.sh deploy/tar/piradio/PiRadioApp

cd deploy/tar
tar -czvf PiRadioApp-$VER.tar.gz piradio

echo ""
echo "Created! You can find out folder in directory /deploy"
echo ""
