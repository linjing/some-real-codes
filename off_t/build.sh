#!/bin/bash

gcc -o off_t.8 main.c  -D_FILE_OFFSET_BITS=64
gcc -o off_t.4 main.c  
