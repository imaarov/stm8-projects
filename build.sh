#!/usr/bin/env bash

set -e

BUILD_DIR="build/Debug"

clean() {
    rm -rf build/Debug/.obj

    find build/Debug -maxdepth 1 -type f \
        ! -name "builder.params" \
        ! -name "compile_commands.json" \
        ! -name "ref.json" \
        ! -name "statistic.json" \
        -delete
}

build() {
    DOTNET_ROLL_FORWARD=Major \
    dotnet "$HOME/.vscode/extensions/cl.eide-3.27.2/res/tools/linux/unify_builder/unify_builder.dll" \
        -p "$BUILD_DIR/builder.params"
}

flash() {
    stm8flash -c stlinkv2 -p stm8s103f3 \
        -w "$BUILD_DIR/stm8s103f3_quickstart_sdcc.hex"
}

case "$1" in
    --clean)
        clean
        ;;
    --clean-build)
        clean
        build
        ;;
    --flash)
        build
        flash
        ;;
    *)
        build
        ;;
esac
