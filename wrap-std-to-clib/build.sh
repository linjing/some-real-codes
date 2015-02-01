g++ -c -o cmap.cpp.o cmap.cpp -I. -fPIC
ld -o libcmap.so  cmap.cpp.o  --shared
ar rs -o libcmap.a  cmap.cpp.o  
g++ -c -o cmap.c.o cmap.c -I. -fPIC
g++ --shared -o libccmap.so cmap.c.o -L. -lcmap
ar rs -o libccmap.a  cmap.c.o  
gcc -o test test.c -I. -L. -lccmap  -lcmap
gcc -o test.s test.c -I. -L. ./libccmap.a ./libcmap.a -lstdc++
