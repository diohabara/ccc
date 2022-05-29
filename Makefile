CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

ccc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): ccc.h

lint:
	./lint.sh

test: ccc
	./test.sh

debug: ccc
	bash -x ./test.sh

clean:
	rm -f ccc *.o *~ tmp*

.PHONY: test clean lint debug