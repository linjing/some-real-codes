g++ -O3 -g -o  BFS_huarongdao huarongdao.cpp  breadth_first_search.cpp  -I . --std=c++0x -pg
./BFS_huarongdao
gprof -q  BFS_huarongdao gmon.out >gmon.out.out
