echo "Creating simple app deploy..."

sh build.sh
cd ..

echo "Assembly simple app deploy..."
echo ""
mkdir -v -p deploy/piradio/PiRadioApp
cp -v help.json deploy/piradio/PiRadioApp
cp -v -r server/resources deploy/piradio/PiRadioApp
cp -v -R example-database.json deploy/piradio/PiRadioApp/radio-database.json

cd build
cp -v PiRadioApp ../deploy/piradio/PiRadioApp
cp -v libPiRadioAppEngineLib.so ../deploy/piradio/PiRadioApp
cp -v server ../deploy/piradio/PiRadioApp
cd ..
cp -v scripts/helpers/simple-deploy/run.sh deploy/piradio/PiRadioApp
cp -v scripts/helpers/simple-deploy/piradio.service deploy/piradio/PiRadioApp
cp -v scripts/helpers/simple-deploy/INSTALL.sh deploy/piradio
cp -v docs/deploy/README.txt deploy/piradio/PiRadioApp

cd deploy
tar -czvf piradio.tar.gz piradio

echo ""
echo "Created! You can find out folder in directory /deploy"
echo ""
