#!/bin/bash
cat <<EOF | gcc -xc -c -o tmp2.o -
int ret3() { return 3; }
int ret5() { return 5; }
int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int add6(int x1, int x2, int x3, int x4, int x5, int x6) { return x1+x2+x3+x4+x5+x6; }
EOF

assert() {
	expected="$1"
	input="$2"

	./ccc "$input" >tmp.s
	gcc -std=c11 -static -o tmp tmp.s tmp2.o
	./tmp
	actual="$?"

	if [ "$actual" = "$expected" ]; then
		echo "$input => $actual"
	else
		echo "$input => $expected expected, but got $actual"
		exit 1
	fi
}

echo 'step1(a single number)' && {
	assert 0 'int main() { return 0; }'
	assert 42 'int main() { return 42; }'
}
echo 'step2(add/subtract numbers)' && {
	assert 21 'int main() { return 5+20-4; }'
}
echo 'step3(tokenizer)' && {
	assert 41 'int main() { return 12 + 34 - 5 ; }'
}
echo 'step5(add, sub, mul, div expressions)' && {
	assert 47 'int main() { return 5+6*7; }'
	assert 15 'int main() { return 5*(9-6); }'
	assert 4 'int main() { return (3+5)/2; }'
}
echo 'step6(unary operator)' && {
	assert 47 'int main() { return +47; }'
	assert 0 'int main() { return -49+49; }'
	assert 10 'int main() { return - - 10; }'
	assert 10 'int main() { return - - +10; }'
}
echo 'step7(comparison operator)' && {
	## eq/ne
	assert 0 'int main() { return 0==1; }'
	assert 1 'int main() { return 42==42; }'
	assert 1 'int main() { return 0!=1; }'
	assert 0 'int main() { return 42!=42; }'
	## lt/le
	assert 1 'int main() { return 0<1; }'
	assert 0 'int main() { return 1<1; }'
	assert 0 'int main() { return 2<1; }'
	assert 1 'int main() { return 0<=1; }'
	assert 1 'int main() { return 1<=1; }'
	assert 0 'int main() { return 2<=1; }'
	## gt/ge
	assert 1 'int main() { return 1>0; }'
	assert 0 'int main() { return 1>1; }'
	assert 0 'int main() { return 1>2; }'
	assert 1 'int main() { return 1>=0; }'
	assert 1 'int main() { return 1>=1; }'
	assert 0 'int main() { return 1>=2; }'
}
echo 'step9(multiple statements separated by a semicolon, single-letter variable)' && {
	## semicolon
	assert 47 'int main() { int a = +48; int b = 2; return +47; }'
	## single-letter variable
	assert 1 'int main() { int a = 1; return a; }'
}
echo 'step10(multi-letter variable)' && {
	assert 33 'int main() { int foo=33; return foo; }'
	assert 4 'int main() { int aho = 3; int futsu = 4; return futsu; }'
}
echo 'step11(return statement)' && {
	assert 14 'int main() { int a = 3; int b = 5 * 6 - 8; return a + b / 2; }'
}
echo 'step12(if, while, for statement)' && {
	## if
	assert 3 'int main() { if (0) return 2; return 3; }'
	assert 3 'int main() { if (1-1) return 2; return 3; }'
	assert 2 'int main() { if (1) return 2; return 3; }'
	assert 2 'int main() { if (2-1) return 2; return 3; }'
	## while
	assert 10 'int main() { int i=0; while(i<10) i=i+1; return i; }'
	## for
	assert 55 'int main() { int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; return j; }'
	assert 3 'int main() { for (;;) return 3; return 5; }'
}
echo 'step13(compound statement)' && {
	assert 3 'int main() { {1; {2;} return 3;} }'
	assert 55 'int main() { int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} return j; }'
}
echo 'step14(function call)' && {
	## zero-arity
	assert 3 'int main() { return ret3(); }'
	assert 5 'int main() { return ret5(); }'
	## multiple arity
	assert 8 'int main() { return add(3, 5); }'
	assert 2 'int main() { return sub(5, 3); }'
	assert 21 'int main() { return add6(1,2,3,4,5,6); }'
}
echo 'step15(function definition)' && {
	## zero-arity
	assert 32 'int main() { return ret32(); } int ret32() { return 32; }'
	## multiple arity
	assert 7 'int main() { return add2(3, 4); } int add2(int x, int y) { return x+y; }'
	assert 1 'int main() { return sub2(4, 3); } int sub2(int x, int y) { return x-y; }'
	assert 55 'int main() { return fib(9); } int fib(int x) { if (x <= 1) return 1; return fib(x-1) + fib(x-2); }'
}
echo 'step16(unary pointer operator)' && {
	assert 1 'int main() { int x=1; return *&x; }'
	assert 2 'int main() { int x=2; int *y=&x; int **z=&y; return **z; }'
	assert 3 'int main() { int x=5; int y=3; return *(&x+1); }'
	assert 4 'int main() { int x=4; int y=5; return *(&y-1); }'
	assert 5 'int main() { int x=3; int *y=&x; *y= 5; return x; }'
	assert 6 'int main() { int x=3; int y=5; *(&x+1)=6; return y; }'
	assert 7 'int main() { int x=3; int y=5; *(&y-1)=7; return x; }'
}
echo 'step17(force type definition and introduce `int` keyword)' && {
	assert 1 'int main() { int x = 5; int y = 4; return pika(&x, y); } int pika(int* x, int y) { return *x - y; }'
}

echo OK
