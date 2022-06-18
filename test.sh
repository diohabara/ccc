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
	gcc -static -o tmp tmp.s tmp2.o
	./tmp
	actual="$?"

	if [ "$actual" = "$expected" ]; then
		echo "$input => $actual"
	else
		echo "$input => $expected expected, but got $actual"
		exit 1
	fi
}

# step1(a single number)
assert 0 '0;'
assert 42 '42;'
# step2(add/subtract numbers)
assert 21 '5+20-4;'
# step3(tokenizer)
assert 41 ' 12 + 34 - 5 ;'
# step5(add, sub, mul, div expressions)
assert 47 '5+6*7;'
assert 15 '5*(9-6);'
assert 4 '(3+5)/2;'
# step6(unary operator)
assert 47 '+47;'
assert 0 '-49+49;'
assert 10 '- - 10;'
assert 10 '- - +10;'
# step7(comparison operator)
## eq/ne
assert 0 '0==1;'
assert 1 '42==42;'
assert 1 '0!=1;'
assert 0 '42!=42;'
## lt/le
assert 1 '0<1;'
assert 0 '1<1;'
assert 0 '2<1;'
assert 1 '0<=1;'
assert 1 '1<=1;'
assert 0 '2<=1;'
## gt/ge
assert 1 '1>0;'
assert 0 '1>1;'
assert 0 '1>2;'
assert 1 '1>=0;'
assert 1 '1>=1;'
assert 0 '1>=2;'
# step 9(multiple statements separated by a semicolon, single-letter variable)
## semicolon
assert 47 '+48; 0 == 1; +47;'
## single-letter variable
assert 1 'a=1;'
# step10(multi-letter variable)
assert 33 'foo=33;'
assert 4 'aho = 3; futsu = 4;'
# step11(return statement)
assert 14 'a = 3; b = 5 * 6 - 8; return a + b / 2;'
# step12(if, while, for statement)
## if
assert 3 'if (0) return 2; return 3;'
assert 3 'if (1-1) return 2; return 3;'
assert 2 'if (1) return 2; return 3;'
assert 2 'if (2-1) return 2; return 3;'
## while
assert 10 'i=0; while(i<10) i=i+1; return i;'
## for
assert 55 'i=0; j=0; for (i=0; i<=10; i=i+1) j=i+j; return j;'
assert 3 'for (;;) return 3; return 5;'
# step13(compound statement)
assert 3 '{1; {2;} return 3;}'
assert 55 'i=0; j=0; while(i<=10) {j=i+j; i=i+1;} return j;'
# step14(function call)
## zero-arity
assert 3 'return ret3();'
assert 5 'return ret5();'
## multiple arity
assert 8 'return add(3, 5);'
assert 2 'return sub(5, 3);'
assert 21 'return add6(1,2,3,4,5,6);'

echo OK