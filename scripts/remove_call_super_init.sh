#!/bin/bash

usage() {
    echo "Usage: $0.sh <directory>"
}

if [ "$#" -eq 1 ]; then
    base_dir="$1"
else
    usage; exit 1
fi

for file in `find $base_dir -type f \( -name "*.h" -or -name "*.inl" -or -name "*.cpp" \)`; do
    perl -pi -e "s/[ \t]+[^\/].*::init\(\);[\n\r]*//g" $file    
    rm -f $file.bak
done

