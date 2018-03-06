yacc -d stage6.y
lex stage6.l
gcc lex.yy.c y.tab.c -w
./a.out smallinp
