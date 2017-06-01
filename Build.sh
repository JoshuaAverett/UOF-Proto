# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

rm -r build &&
mkdir -p build &&
cd build &&
cmake .. &&
make &&
valgrind ./unit-tests/unit-tests ||
./unit-tests/unit-tests
