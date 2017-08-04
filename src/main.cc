// MIT License
//
// Copyright (c) 2017 Thiago Vieira
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.




//  Given a set of documents, with the level of relevance and type
//    of each document.
//
//  This piece of code returns a subset of size k that maximizes the
//     F Score.
//
//  *** Don't mind the jokes on the code :) ***
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include "ilcplex/ilocplex.h"
using namespace std;
ILOSTLBEGIN

#define EPS 1e-7
#define MAXN 1000
#define MAXM 2000
#define MAX_BB_ITER 20000

const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3fll;


int n, m, k = 0;

// Matrix of 0's and 1's, defining if document i is of type j.
int vt[MAXN][MAXM];

// The precision of each document.
double vp[MAXN];


// The function solve returns true if the model has a solution given theta1 and theta2.
// Theta1 is the constant attached to the variable X of the model.
// Theta2 is the constant attached to the variable Y of the model.
// If you want all logs to be printed, just set verbose to true; it's false by default.
bool solve(double theta1, double theta2, bool verbose=false)
{
  bool deubom = false;
  
  // And now comes the formulation... 
  try {
    IloEnv env;
    IloModel model(env);
    
    IloExpr precisionexpr(env);
    IloExpr typesexpr(env);
    IloExpr maxXSum(env);
    IloIntVarArray Y(env, m, 0, 1);
    IloIntVarArray X(env, n, 0, 1);
    IloNumArray precisionarray(env, n);
    
    for(int i = 0; i < n; i++)
      precisionarray[i] = vp[i];
    
    for(int i = 0; i < m; i++)
    {
      IloExpr rhs(env);
      for(int j = 0; j < n; j++)
        rhs += vt[j][i] * X[j];

      model.add(Y[i] <= rhs);
      typesexpr += Y[i];
    }
    
   
    for(int i = 0; i < n; i++)
      maxXSum += X[i];
    
    model.add(maxXSum == k);
    IloNumVar theta(env);
    IloExpr sx = IloScalProd(precisionarray, X);
    IloExpr sy = typesexpr;
    
    model.add(theta1*sx >= 1);
    model.add(theta2*sy >= 1);
    model.add(theta == theta1+theta2);
    model.add(IloMinimize(env, theta));

    IloCplex cplex(model);
    cplex.setOut(env.getNullStream());
    deubom = cplex.solve();
    if(verbose) {
      if(!deubom) {
        env.error() << "Falhou para otimizar" << endl;
      }
      else
      {
        IloNumArray valsx(env, n);
        IloNumArray valsy(env, m);

        env.out() << "Solution Status = " << cplex.getStatus() << endl;
        env.out() << "Solution Value = " << cplex.getObjValue() << endl;

        // Printing result's values.
        cplex.getValues(valsx, X);
        env.out() << "X Values = " << valsx << endl << endl;

        cplex.getValues(valsy, Y);
        env.out() << "Y Values = " << valsy << endl;
      }
    }
    env.end();
  }
  catch(IloException &e) {
    std::cerr << "HEAUHEAUUHA ";
    std::cerr << "SABE NEM CODAR A PARADA\n" << e << endl;
    deubom = false;
  }
  return deubom;
}


int main()
{
  // Expected Input:
  // 
  // Three integers: n, m and k.
  //  n representing the number of documents
  //  m representing the number of types of documents.
  //  k representing the number of documents that will be selected. 
  //
  // n lines:
  //  For each line there is a float p, the precision of the i-th document.
  // 
  // n lines:
  //  For each line there is an integer x, the number of types assigned to the i-th document.
  //  The integer x is followed by x other integers, the types of the document.
  // 
  // Everything here is 0-based.
  


  // Cleaning everything
  memset(vt, 0, sizeof(vt));
  for(int i = 0; i < MAXN; i++)
    vp[i] = 0;
  
  
  // Reading the input.
  cin >> n >> m >> k;
  for(int i = 0; i < n; i++)
    cin >> vp[i];
  
  for(int i = 0; i < n; i++)
  {
    int x, t;
    cin >> x;
    for(int j = 0; j < x; j++)
    {
      cin >> t;
      vt[i][t] = 1;
    }
  }
  
  
  double theta = INF;
  double best_theta1 = 1;
  double best_theta2 = 1;
  
  
  
  // Since theta2 is the variable associated with the Y variable,
  // It must go from 1 to m.
  for(int theta2 = 1; theta2 <= m; theta2++)
  {
    // And now the binary search comes...
    // Since theta1 is the variable associated with the X variable.
    // It must go from EPS to a large value fixed here as 10000,
    // since getting all documents not relevant
    // is a viable solution, as well as getting K super relevant documents.
    // Super relevant = (precision = 1).
    // Remember that the constraint is theta1 <= 1/\sum{p_i*x_i}.
    
    double b_theta1 = 10000;
    double e_theta1 = EPS;
    int iter = 0;
    
    while(fabs(e_theta1 - b_theta1) > EPS && iter < MAX_BB_ITER)
    {
      iter++;
      double mid_theta1 = (b_theta1 + e_theta1)/2;
      if(solve(mid_theta1, 1.0f/theta2))
      {
        double neue_theta = mid_theta1 + 1.0f/theta2;
        if(neue_theta < theta)
        {
          theta = neue_theta;
          best_theta1 = mid_theta1;
          best_theta2 = theta2;
        }
        b_theta1 = mid_theta1;
      }
      else e_theta1 = mid_theta1+EPS;
    }
    if(iter == MAX_BB_ITER) cout << "Estourou\n";
  }
  
  cout << "Theta 1: " << best_theta1 << endl;
  cout << "Theta 2: " << best_theta2 << endl;
  // Resolving with the best theta1 and theta2 found.
  // And printing everything as well.
  solve(best_theta1, 1.0f/best_theta2, true);
  
  cout << std::fixed << std::setprecision(4);
  cout << best_theta1 + 1.0f/best_theta2 << endl;

  return 0;
}
