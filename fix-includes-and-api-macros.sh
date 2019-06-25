#!/bin/bash

cd  "$1"

grep -ri '#include "config.h"' --include=\*.{cpp,h,inl} | while read line; do
    file="$(echo "$line" | sed -e 's/:.*$//')"
    string_to_replace="$(echo "$line" | sed -e 's/^.*://')"
    module="$(echo "$line" | sed -e 's/\/.*$//')"
    module_uppercase="$(echo ${module^^})"
    
    sed -i -e 's/^'"$string_to_replace"'$/#include <'"$module"'\/config.h>/g' "$file"
    
    sed -i -e 's/SOFA_[A-Z_]*_API/SOFA_'"$module_uppercase"'_API/g' "$file"
    
    exit 0
done
