# ccc

[![ci](https://github.com/diohabara/ccc/actions/workflows/ci.yaml/badge.svg)](https://github.com/diohabara/ccc/actions/workflows/ci.yaml)

An experimental C compiler.

## how to develop

If you develop in [`Dev Container`](https://code.visualstudio.com/docs/remote/containers), you do not have to put `docker run --platform=linux/amd64 -v "${PWD}:src" -w/src ccc` at the top of commands. You simply execute `make test`, for example.

### dependencies

- [`docker`](https://www.docker.com/)

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
docker run --platform=linux/amd64 -v "${PWD}:src" -w/src ccc make lint
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
