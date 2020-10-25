echo "Create deploy..."

mkdir -p deploy/piradio
cp build/PiRadioApp deploy/piradio/
cp build/server deploy/piradio/
cp build/libPiRadioAppEngineLib.so deploy/piradio/
cp -r server/resources deploy/piradio/
mkdir deploy/piradio/database
touch deploy/piradio/database/radio-stations.json
cp run.sh deploy/piradio
mv deploy/piradio /home/$USER/

echo "Done."
