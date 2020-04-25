#!/usr/bin/env bash

set -euo pipefail

thisfile=$(python -c "import os;print(os.path.realpath('${BASH_SOURCE[0]}'))")
thisdir=$(dirname "${thisfile}")

if [[ -d "${thisdir}/neither-0.5.0" ]]; then
    exit 0
fi

wget -qO - https://github.com/LoopPerfect/neither/archive/v0.5.0.tar.gz | tar -xz
cd "neither-0.5.0/neither" || exit 1
mv include neither
