#!/bin/sh
rm -rvf build
rm -rf coverage*
set -e
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCFL_GEN_COVERAGE=1 ../..
make
valgrind --error-exitcode=1 ./tests
cd ..
lcov --capture --directory build/CMakeFiles/cfl_core.dir/ --directory build/CMakeFiles/cfl_test.dir/ --output-file coverage.info
genhtml coverage.info --output-directory coverage
