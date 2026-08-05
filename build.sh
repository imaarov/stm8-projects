#!/usr/bin/env bash

set -e

build() {
    DOTNET_ROLL_FORWARD=Major \
    dotnet "$HOME/.vscode/extensions/cl.eide-3.27.2/res/tools/linux/unify_builder/unify_builder.dll" \
    -p build/Debug/builder.params
}

flash() {
    stm8flash -c stlinkv2 -p stm8s103f3 -w build/Debug/stm8s103f3_quickstart_sdcc.hex
}

build

if [[ "$1" == "--flash" ]]; then
    flash
fi
