#!/bin/bash

# sudo yum -y install uuid-devel
# sudo apt -y install uuid-dev

# - clone code
# git clone https://github.com/brinkqiang/dmcinatra.git
# pushd dmcinatra
# git submodule update --init --recursive
#

# pushd thirdparty/depends_path
# libtoolize && aclocal && autoheader && autoconf && automake --add-missing
# sh configure
# popd

rm -rf build
mkdir -p build
pushd build
cmake -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo
popd

# popd

# echo continue && read -n 1
