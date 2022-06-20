# ccc

[![ci](https://github.com/diohabara/ccc/actions/workflows/ci.yaml/badge.svg)](https://github.com/diohabara/ccc/actions/workflows/ci.yaml)

An experimental C compiler.

## how to develop

### dependencies

To compile

- `docker`

To lint

- `make`
- `shellcheck`
- `clang-format`

### build

```bash
docker build . -t ccc
```

### help

```bash
docker run --platform=linux/amd64 -v "${PWD}:src" -w/src ccc make help
```

### lint/format

```bash
make lint
```

### test

When you want to see if the compiler is working,

```bash
docker run --platform=linux/amd64 -v "${PWD}:src" -w/src ccc make test
```

When you debug something about the testing,

```bash
docker run --platform=linux/amd64 -v "${PWD}:src" -w/src ccc make debug
```

### debug

If you want to debug interactively, use `gdb`.

```bash
docker run -i --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --platform=linux/amd64 -v "${PWD}:/src" -w/src ccc bash -c "make; gdb ./ccc"
```

If you want to debug `main() { a = 1; b = 2; return 3; }` in `gdb`,

```gdb
r 'main() { a = 1; b = 2; return 3; }'
```

### clean

When you want to remove object files,

```bash
make clean
```

## references

- <https://www.sigbus.info/compilerbook>
- <https://github.com/rui314/ccc>
- <https://github.com/rui314/ccc/tree/reference>
