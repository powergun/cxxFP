#!/usr/bin/env bash

set -euo pipefail

# parameters
version="${1:?missing version!}"
dest=$(python -c "import os;print(os.path.realpath('${2:-.}'))")

# static
thisfile=$(python -c "import os;print(os.path.realpath('${BASH_SOURCE[0]}'))")
thisdir=$(dirname "${thisfile}")
para=$(python -c "import multiprocessing as m;print(m.cpu_count())")

download_untar() {
    local version_=$(perl -wnl -E 's/\./_/g; say' <<<${version})
    local filename="boost_${version_}"
    local fext="${filename}.tar.bz2"
    if [[ ! -f "${fext}" ]]; then
        local downloadurl="https://dl.bintray.com/boostorg/release/${version}/source/${fext}"
        wget "${downloadurl}"
    fi
    if [[ ! -d "${filename}" ]]; then
        tar -xf "${filename}.tar.bz2"
    fi
    echo -n "${filename}"
}

do_install() {
    local link=${1:?missing link param (static or dynamic)}
    ./b2 -j "${para}" install cxxflags='-fPIC' cflags='-fPIC' --link="${link}" --prefix="${dest}"
}

cd /tmp
d=$(download_untar)
cd "${d}" && ./bootstrap.sh
do_install "dynamic"
do_install "static"

