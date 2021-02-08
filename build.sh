#!/bin/bash

# - clone code
# git clone https://github.com/brinkqiang/dmcinatra.git
# pushd dmcinatra
# git submodule update --init --recursive
#

# pushd thirdparty/depends_path
# libtoolize && aclocal && autoheader && autoconf && automake --add-missing
# sh configure
# popd
if [ -f /etc/redhat-release ]; then
    sudo yum -y install uuid-devel
fi

if [ -f /etc/lsb-release ]; then
    sudo apt -y install uuid-dev
fi

rm -rf build
mkdir -p build

pushd build
cmake -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo

popd

# popd

# echo continue && read -n 1
