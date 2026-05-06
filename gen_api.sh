#!/bin/bash

if [ -z "$1" ]; then
  echo "Provide class name"
  exit 1
fi
if [ -z "$2" ]; then
  echo "Provide description"
  exit 1
fi

TITLE=$1
DESCRIPTION=$2
FILENAME="docs/API/${TITLE}.md

cat <<EOF > "$FILENAME"
---
layout: default
title: $TITLE
parent: API Reference
description: $DESCRIPTION

# $TITLE
$DESCRIPTION

EOF

echo "Created $FILENAME"
