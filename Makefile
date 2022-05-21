CFLAGS=-std=c11 -g -static

ccc: ccc.c

lint:
	./lint.sh

test: ccc
	./test.sh

debug: ccc
	bash -x ./test.sh

clean:
	rm -f ccc *.o *~ tmp*

.PHONY: test clean lint debug