#!/usr/bin/env python
#coding: utf-8

from sys import argv, stdout
from random import randint
from random import uniform

def main():
  n = randint(5, 12)
  m = randint(2, 10)
  k = randint(1, 5)
  
  
  print n, m, k
  for i in range(n):
    print uniform(0, 1)
  
  for i in range(n):
    vtypes = [randint(0, 1) for j in range(m)]
    
    cnt = 0;
    for j in range(m):
      if vtypes[j] == 1:
        cnt += 1
    stdout.write(str(cnt))

    for j in range(m):
      if vtypes[j] == 1:
        stdout.write(" " + str(j))
    stdout.write("\n")
  

if __name__ == '__main__':
  main()
