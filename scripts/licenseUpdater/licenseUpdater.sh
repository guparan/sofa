#!/bin/bash

usage() {
    echo "Usage: licenseUpdater.sh <src-dir> <license> <year> <version> <application> <copyright>"
    echo "  src-dir: all files in this folder will be affected"
    echo "  license: choose in ['auto', 'LGPL', 'GPL', 'LGPL-app', 'GPL-app', 'ZLIB-app']"
    echo "  year: YYYY formatted year for the copyright"
    echo "  version (ignored in applications): SOFA version"
    echo "  application (applications only): name of your application"
    echo "  copyright (applications only): copyright including year ; e.g. '2017 John Smith, Martin Dupond'"
}

if [[ "$#" -ge 4 ]]; then
    SRC_DIR="$1"
    LICENSE="$2"
    YEAR="$3"
    VERSION="$4"
    APPLICATION="$5"
    COPYRIGHT="$6"

    VERSION_TAG="____VERSION_NUMBER____"
    YEAR_TAG="YYYY"
    APPLICATION_TAG="______________________APPLICATION______________________"
    COPYRIGHT_TAG="______________________COPYRIGHT______________________"
else
    usage; exit 1
fi

if [ ${#VERSION} -gt ${#VERSION_TAG} ]; then
    echo "ERROR: <version> length can be ${#VERSION_TAG} chars max."; exit 1
elif [ ${#YEAR} -gt ${#YEAR_TAG} ]; then
    echo "ERROR: <year> length can be ${#YEAR_TAG} chars max."; exit 1
elif [ ${#APPLICATION} -gt ${#APPLICATION_TAG} ]; then
    echo "ERROR: <application> length can be ${#APPLICATION_TAG} chars max."; exit 1
elif [ ${#COPYRIGHT} -gt ${#COPYRIGHT_TAG} ]; then
    echo "ERROR: <copyright> length can be ${#COPYRIGHT_TAG} chars max."; exit 1
fi

if [ ! -d "$SRC_DIR" ]; then
    usage; exit 1
fi

files-to-update() {
    /usr/bin/find "$SRC_DIR" -regex ".*\.\(h\|cpp\|inl\|c\|cu\|h\.in\)$"
}

get-license() {
    file="$1"
    if grep -q "^\*[ ]*SOFA, Simulation Open-Framework Architecture" "$file"; then
        if grep -q "GNU Lesser General Public License" "$file" && grep -q "GNU General Public License" "$file"; then
            echo "multiple";
        elif grep -q "GNU Lesser General Public License" "$file"; then
            echo "LGPL";
        elif grep -q "GNU General Public License" "$file"; then
            echo "GPL";
        else
            echo "other";
        fi
    else
        echo "none";
    fi
}

set-year() {
    echo "$(perl -p -e "s/$YEAR_TAG/$YEAR/g" $1)"
}

set-version() {
    local tag_size=${#VERSION_TAG}
    local version="$VERSION"
    local version_size=${#version}

    while [ $version_size -lt $tag_size ]; do
        version+=' '
        version_size=${#version}
    done

    echo "$(perl -p -e "s/$VERSION_TAG/$version/g" $1)"
}

set-application() {
    local tag_size=${#APPLICATION_TAG}
    local application="$APPLICATION"
    local application_size=${#application}

    if [ -z "$application" ]; then
        echo "WARNING: no application given." >&2
    fi

    while [ $application_size -lt $tag_size ]; do
        if [ $(($application_size % 2)) = 0 ]; then
            application="$application "
        else
            application=" $application"
        fi
        application_size=${#application}
    done
    
    echo "$(perl -p -e "s/$APPLICATION_TAG/$application/g" $1)"
}

set-copyright() {
    local tag_size=${#COPYRIGHT_TAG}
    local copyright="$COPYRIGHT"
    local copyright_size=${#copyright}
    
    if [ -z "$copyright" ]; then
        echo "WARNING: no copyright given." >&2
    fi

    while [ $copyright_size -lt $tag_size ]; do
        if [ $(($copyright_size % 2)) = 0 ]; then
            copyright="$copyright "
        else
            copyright=" $copyright"
        fi
        copyright_size=${#copyright}
    done

    echo "$(perl -p -e "s/$COPYRIGHT_TAG/$copyright/g" $1)"
}

# prepare-header <file>
prepare-header() {
    if [ ! -e "$1" ]; then
        echo "$1: file not found."; exit 1
    fi
    set-year "$1" | set-version | set-application | set-copyright
}

escape-for-perl() {
    #                   * becomes \*                  / becomes \/               @ becomes \@                ( becomes \(               ) becomes \)
    echo "$(perl -p -e 's/\*/\\\*/g' $1 | perl -p -e 's/\//\\\//g' | perl -p -e 's/\@/\\\@/g' | perl -p -e 's/\(/\\\(/g' | perl -p -e 's/\)/\\\)/g')"
}

update-header() {
    header="$1"
    file="$2"
    escaped_header="$(echo "$header" | escape-for-perl)"
    # search for /***(78)***...SOFA, Simulation Open-Framework Architecture...***(78)***/ and replace with escaped header
    perl -0777 -i -pe "s/(\/)(\*){78}(.*?)SOFA, Simulation Open-Framework Architecture(.*?)(\*){78}(\/)/$escaped_header/s" "$file"
    rm "$file.bak" 2> /dev/null # Created by Windows only
}

main() {
    if [ "$LICENSE" == "auto" ]; then
        if [ ! -e "./LGPL_header.template" ] || [ ! -e "./GPL_header.template" ]; then
            echo "ERROR: missing LGPL_header.template and/or GPL_header.template in $(pwd)"; exit 1
        fi
        LGPL_HEADER="$(prepare-header ./LGPL_header.template)"
        GPL_HEADER="$(prepare-header ./GPL_header.template)"
    else
        file="./"$LICENSE"_header.template"
        if [ ! -e "$file" ]; then
            echo "ERROR: missing $file in $(pwd)"; exit 1
        fi
        LICENSE_HEADER="$(prepare-header "$file")"
    fi

    local files_count="$(files-to-update | wc -l)"
    local i=1

    files-to-update | while read file; do
        if [ ! -e "$file" ]; then
            echo "$file: file not found."
            continue
        fi

        current_license="$(get-license "$file")"

        if [ "$LICENSE" == "auto" ]; then
            case "$current_license" in
                "LGPL")
                    update-header "$LGPL_HEADER" "$file"
                    echo "$file updated with LGPL"
                    ;;
                "GPL")
                    update-header "$GPL_HEADER" "$file"
                    echo "$file updated with GPL"
                    ;;
                *)
                    echo "WARNING: $file not changed. License detected: $current_license"
                    ;;
            esac
        else # [ $LICENSE != "auto" ]
            case "$current_license" in
                "none")
                    # add new license header
                    printf "$LICENSE_HEADER\n$(cat "$file")" > "$file"
                    ;;
                "multiple")
                    echo "WARNING: $file not changed. License detected: multiple"
                    ;;
                *)
                    update-header "$LICENSE_HEADER" "$file"
                    echo "$file updated with $LICENSE"
                    ;;
            esac
        fi        
        (>&2 echo -ne "Updating: $i / $files_count\r")
        ((i++))
    done
}

# Start script
main