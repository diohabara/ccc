CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

ccc: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(OBJS): ccc.h

STAGES = stage1 stage2 stage3

define PROCESS_STAGE_RULE
$(1)/%.c: %.c
	mkdir -p $(1)
	gcc -E $$< | grep -v '^#' > $$@
endef

$(foreach stage,$(STAGES),$(eval $(call PROCESS_STAGE_RULE,$(stage))))

PROCESSED_SRCS = $(foreach stage,$(STAGES),$(addprefix $(stage)/,$(SRCS)))

process: $(PROCESSED_SRCS)

help:
	@echo "Usage: make [lint|test|debug|clean|process]"
	@echo "  lint: run c and shell checker"
	@echo "  test: run tests"
	@echo "  debug: run tests in debug mode"
	@echo "  clean: remove object files"
	@echo "  process: run the preprocessor on all source files for each stage"

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

.PHONY: help lint test clean process
