#!/bin/bash



rm -r RATP_GTFS_LINES
wget http://dataratp.download.opendatasoft.com/RATP_GTFS_LINES.zip
unzip RATP_GTFS_LINES.zip -d RATP_GTFS_LINES
rm RATP_GTFS_LINES.zip
cd RATP_GTFS_LINES
for i in 1 2 3 3b 4 5 6 7 7b 8 9 10 11 12 13 14 Fun Orv
do
    unzip RATP_GTFS_METRO_$i.zip -d RATP_GTFS_METRO_$i
done
find . -name "*.zip" -delete
cd ..

