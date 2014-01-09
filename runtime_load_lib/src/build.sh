g++ -c -o hello_printf.o hello_printf.cpp 
g++ --shared -o hello_printf.so hello_printf.o

g++ -c -o hello_cout.o hello_cout.cpp
g++ --shared -o hello_cout.so hello_cout.o

g++ -o test load_lib.cpp  -I. -ldl
