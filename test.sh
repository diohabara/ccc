#!/bin/bash
assert() {
	expected="$1"
	input="$2"

	./ccc "$input" >tmp.s
	cc -o tmp tmp.s
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
assert 0 0
assert 42 42
# step2(add/subtract numbers)
assert 21 "5+20-4"
# step3(tokenizer)
assert 41 " 12 + 34 - 5 "

echo OK