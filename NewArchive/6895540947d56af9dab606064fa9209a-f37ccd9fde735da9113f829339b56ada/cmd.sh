gcc -x c -W -Wextra -pedantic main.cpp && ./a.out && objdump -s -j .rodata a.out