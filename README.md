# ccc

[![ci](https://github.com/diohabara/ccc/actions/workflows/ci.yaml/badge.svg)](https://github.com/diohabara/ccc/actions/workflows/ci.yaml)

An experimental C compiler.

## how to develop

If you're using Ubuntu, you can use the commands without `x`.

### dependencies

- [`docker`](https://www.docker.com/)

### build

When you want to build Docker env,

```bash
docker build . -t ccc
```

### help

When you want to know what options exist,

```bash
make help
```

### lint/format

When you want to check/format source code,

```bash
make lint
```

### test

When you want to see if the compiler is working,

```bash
make test
```

### debug

If you want to debug interactively, use `gdb`.

```bash
gdb ./ccc
```

If you want to debug `main() { a = 1; b = 2; return 3; }` in `gdb`,

```bash
r 'main() { a = 1; b = 2; return 3; }'
```

### clean

When you want to remove object files,

```bash
make clean
```

## TODO

- [ ] self host
  - `make self-host`

## references

- <https://www.sigbus.info/compilerbook>
- <https://github.com/rui314/chibicc>

