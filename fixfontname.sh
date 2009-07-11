#!/bin/bash
file=$1
if [ ! -f "$file" ]; then
    exit 1
fi
face=`./fontinfo "$file" | grep Face: | cut -f 2 | sed "s/ \+/-/g"`
newfile=`dirname "$file"`/$face.ttf
if [ "$newfile" = "$file" ]
then
    echo $file seems to be named correctly.
else
    if [ -f "$newfile" ]
    then
        if [ `md5sum "$file" | cut -d" " -f1` = `md5sum "$newfile" | cut -d" " -f1` ]
        then
            echo Detected duplicate: $file
            rm $file
        else
            echo Are $file and $newfile duplicates?
        fi
    else
        echo $file -\> $newfile
        mv "$file" "$newfile"
    fi
fi
