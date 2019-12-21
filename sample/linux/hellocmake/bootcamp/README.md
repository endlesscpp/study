#### demostrate how to integrate GTest with cmake

steps:

- mkdir build && cd build
- cmake ..
- make
- run the test/test_BOOTCAMP or run ctest
- use 'export GTEST_COLOR=1' if want to color the ctest output.

If want to install, you can 
- set the install dir prefix: cmake -DCMAKE_INSTALL_PREFIX=/tmp/t2 ..
- install: make install

