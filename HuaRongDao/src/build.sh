#!/bin/bash
#flags -pg  -DDEBUG=1 to test
g++ -O3 -g -o  BFS_huarongdao huarongdao.cpp  breadth_first_search.cpp  -I . --std=c++0x 
