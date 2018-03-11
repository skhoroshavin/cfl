#!/bin/sh
rm -rf coverage*
mkdir test
cd test
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCFL_GEN_COVERAGE=1 ../..
make
valgrind --error-exitcode=1 ./tests
cd ..
lcov --capture --directory test/CMakeFiles/cfl_core.dir/ --directory test/CMakeFiles/cfl_test.dir/ --output-file coverage.info
genhtml coverage.info --output-directory coverage
rm -rf test
