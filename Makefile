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

test: ccc
	./ccc tests > tmp.s
	gcc -static -o tmp tmp.s
	./tmp

clean:
	rm -f ccc *.o *~ tmp*

.PHONY: help lint test lean
