#!/bin/bash
#  Simple bash code to check the corretude of the formulation by stress testing.
#
#  Before stress-testing, remember to set the main code to just output the
#  inverse of the F function, with exactly 4 precision digits.

g++ brute_force.cc -std=c++11 -o brute_force -Wall -O2
cd ../../src/
make
cd -
mv ../../src/main .

echo "Stress Testing..."
for i in {1..20}; do
  echo "Test $i"
  python generate_random_test.py > tmp_test
  ./main < tmp_test > main_output
  ./brute_force < tmp_test > brute_force_output
  diff main_output brute_force_output
done


rm brute_force
rm main
rm tmp_test
rm main_output
rm brute_force_output
