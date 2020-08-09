#!/usr/bin/env bash
pwd=`pwd`

mkdir tmp
cd tmp
git clone https://github.com/KjellKod/g3log.git
cd g3log
mkdir -p  build_travis
cd build_travis
cmake -DADD_G3LOG_UNIT_TEST=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
  make -j && sudo make install
cmake --build . --target install

cd $pwd
cd g3log_integration
mkdir build 
cd build 
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/local .. 
cmake --build . 
LD_LIBRARY_PATH=/usr/local/lib/ ./example_g3log



cd $pwd
cd g3sinks_integration
mkdir build
cd build 
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/local .. 
cmake --build . 
 LD_LIBRARY_PATH=/usr/local/lib/ ./example_g3sinks

