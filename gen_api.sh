#!/bin/bash

PWD=$(pwd)

rm -rf xml/ docs/API/*
# mkdir -p docs/API/

doxygen Doxyfile2
doxybook2 --input xml --output docs/API #--config $PWD/doxybook2.config.json

find docs/API -type f -name "*.md" | while read -r file; do
    if [[ "$file" == "docs/API/index.md" ]]; then continue; fi

    EXISTING_TITLE=$(grep -m 1 "^title: " "$file" | sed 's/title: //')
    
    if [ -z "$EXISTING_TITLE" ]; then
        EXISTING_TITLE=$(grep -m 1 "^# " "$file" | sed 's/# //')
    fi

    {
        echo "---"
        echo "layout: default"
        echo "parent: API Reference"
        if [ ! -z "$EXISTING_TITLE" ]; then
            echo "title: \"$EXISTING_TITLE\""
        fi
        echo "---"
        echo ""
        sed '/^---$/,/^---$/d' "$file"
    } > "${file}.tmp"

    mv "${file}.tmp" "$file"
done

# rm -f docs/API/index_examples.md
# rm -f docs/API/index_files.md
# rm -f docs/API/index_groups.md
# rm -f docs/API/index_pages.md

# rm -rf docs/API/Examples/
# rm -rf docs/API/Files/
# rm -rf docs/API/images/
# rm -rf docs/API/Modules/
# rm -rf docs/API/Pages/

# rm -f docs/API/Namespaces/namespace____Archive.md
# rm -f docs/API/Namespaces/namespaceDEFAULT__INSTANTIATORS.md

echo "API Docs mashed"