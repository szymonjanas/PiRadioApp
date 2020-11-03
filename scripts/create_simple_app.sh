echo "Creating simple app deploy..."

sh build.sh
cd ..

echo "Assembly simple app deploy..."
echo ""
mkdir -v -p deploy/PiRadioApp
cp -v help.json deploy/PiRadioApp
cp -v -r server/resources deploy/PiRadioApp
cp -v -R example-database.json deploy/PiRadioApp/radio-database.json

cd build
cp -v PiRadioApp ../deploy/PiRadioApp
cp -v libPiRadioAppEngineLib.so ../deploy/PiRadioApp
cp -v server ../deploy/PiRadioApp
cd ..
cp -v -R scripts/helpers/run_simple_app.sh deploy/PiRadioApp/run.sh

echo ""
echo "Created! You can find out folder in directory /deploy"
echo ""
