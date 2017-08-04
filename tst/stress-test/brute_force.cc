// Code that solves the same problem by just brute-forcing all solutions.
//
//  Input: The same input expected by the main code.
//
//  Output: It outputs just a real number with 6 precision digits.
//          It outputs the inverse of the F function.
//
//  Before stress-testing, remember to set the main code to just output the
//  inverse of the F function, with exactly 4 precision digits.

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  
  int n, m, k;
  vector<int> vmask, vtypes;
  vector<double> vprecision;

  cin >> n >> m >> k;
  vmask.resize(n, 0);
  vprecision.resize(n, 0);
  vtypes.resize(n, 0);
  int last = vmask.size()-1, tmp = k;
  while(tmp--) vmask[last--] = 1;
  
  for(int i = 0; i < n; i++)
    cin >> vprecision[i];
  
  
  for(int i = 0; i < n; i++) {
    int x, inp;
    cin >> x;
    while(x--) {
      cin >> inp;
      vtypes[i] |= (1<<inp);
    }
  }
  
  double best_f_inverse = 10000000;
  
  do {
    double precisionsum = 0;
    int mask_types = 0;
    for(int i = 0; i < n; i++)
    {
      if(vmask[i])
      {
        precisionsum += vprecision[i];
        mask_types |= vtypes[i];
      }
    }
    
    double f_inverse = (1.0f/precisionsum) + (1.0f/__builtin_popcount(mask_types));
    if(f_inverse < best_f_inverse) best_f_inverse = f_inverse;
  } while(next_permutation(vmask.begin(), vmask.end()));
  
  
  cout << std::fixed << std::setprecision(4);
  cout << best_f_inverse << endl;
  
  return 0;
}
