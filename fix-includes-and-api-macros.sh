#!/bin/bash

cd  "$1"
(
grep -ri 'SOFA_.*_API' --include=\*.{cpp,h,inl}
grep -ri '#include "config.h"' --include=\*.{cpp,h,inl}
) | sed -e 's/:.*$//' | sort | uniq | while read filepath; do
    module="$(echo "$filepath" | sed -e 's/\/.*$//')"
    
    if [[ "$module" == "core" ]]; then
        module="SofaCore"
    elif [[ "$module" == "defaulttype" ]]; then
        module="SofaDefaultType"
    elif [[ "$module" == "helper" ]]; then
        module="SofaHelper"
    elif [[ "$module" == "simulation" ]]; then
        module="SofaSimulation"
    fi
    
    module_uppercase="$(echo ${module^^})"

    sed -i -e 's/^#include "config.h"$/#include <'"$module"'\/config.h>/g' "$filepath"
    sed -i -e 's/^#include <config.h>$/#include <'"$module"'\/config.h>/g' "$filepath"
    
    sed -i -e 's/SOFA_[A-Z_]*_API/SOFA_'"$module_uppercase"'_API/g' "$filepath"
    
done
