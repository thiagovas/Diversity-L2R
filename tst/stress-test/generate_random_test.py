#!/usr/bin/env python
#coding: utf-8

from sys import argv, stdout
from random import randint
from random import uniform

def main():
  n = randint(5, 20)
  m = randint(2, 20)
  k = randint(1, n)
  
  
  print n, m, k
  for i in range(n):
    print uniform(0, 1)
  
  for i in range(n):
    x = randint(0, m)
    stdout.write(str(x))
    vtypes = [randint(0, 1) for j in range(x)]
    
    for j in range(x):
      if vtypes[j] == 1:
        stdout.write(" " + str(j))
    stdout.write("\n")
  

if __name__ == '__main__':
  main()
