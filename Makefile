CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

ccc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJS): ccc.h

help:
	@echo "Usage: make [lint|test|debug|clean]"
	@echo "  lint: run c and shell checker"
	@echo "  test: run tests"
	@echo "  debug: run tests in debug mode"
	@echo "  clean: remove object files"

lint:
	clang-format -i ./*.c
	clang-format -i ./*.h

lintx:
	docker run --platform=linux/amd64 -v "${PWD}:/src" -w/src ccc make lint

test: ccc
	./ccc tests > tmp.s
	echo 'int char_fn() { return 257; }' | gcc -xc -c -o tmp2.o -
	gcc -static -o tmp tmp.s tmp2.o
	./tmp

testx:
	docker run --platform=linux/amd64 -v "${PWD}:/src" -w/src ccc make test

clean:
	rm -f ccc *.o *~ tmp*

.PHONY: help lint test lean
