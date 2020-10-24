#!/bin/sh
cp piradio.service /etc/systemd/system
rm piradio.service
mkdir ~/piradio
cp . ~/piradio
