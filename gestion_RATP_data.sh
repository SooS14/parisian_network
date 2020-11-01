#!/bin/bash

condition=0

if [ -d RATP_GTFS_LINES ]
then
    cd RATP_GTFS_LINES
    for i in 1 2 3 3b 4 5 6 7 7b 8 9 10 11 12 13 14 Fun Orv
    do
        if [ ! -d RATP_GTFS_METRO_$i ]
        then
      	    condition=1
	fi
    done
    cd ..
else
    condition=2
fi



if [ "$condition" -eq "1" ]
then
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
fi


if [ "$condition" -eq "2" ]
then
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
fi


if [ "$condition" -eq "0" ]
then
    echo "RATP_GTFS_LINES est a jour"
fi

