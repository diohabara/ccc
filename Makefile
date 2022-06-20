CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

.PHONY: help test clean lint debug

help:
	@echo "Usage: make [lint|test|debug|clean]"
	@echo "  lint: run c and shell checker"
	@echo "  test: run tests"
	@echo "  debug: run tests in debug mode"
	@echo "  clean: remove object files"

$(OBJS): ccc.h

ccc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

lint:
	./lint.sh

test: ccc
	./test.sh

debug: ccc
	bash -x ./test.sh

clean:
	rm -f ccc *.o *~ tmp*
