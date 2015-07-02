pthread_qsort
=============

a quick sort function in pthread

# Compile 
  g++ *.c -lpthread

# Usage
  ./a.out 4 input.txt output.txt

# Input data format
一個數字即換行，無最後一行留白。

# Params
`argv[1]`: number of threads
`argv[2]`: input file
`argv[3]`: output file
