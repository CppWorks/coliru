set -x
echo -e "#include <stdio.h>\nint main(){printf( \"hello world\\\n\" ) ; return 0 ;}"  | gcc -x c - && ./a.out