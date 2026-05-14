#!/bin/bash

makeb=make
eres='\e[0m'
ecia='\e[36m'

if ! dpkg -l "libsdl2-dev" &>/dev/null; then
    echo "err: libsdl2-dev is not installed"
    exit 1
fi

echo -e "${ecia}"

$makeb all
$makeb run

echo -e "${eres}"