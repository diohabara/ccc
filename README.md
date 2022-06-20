# ccc

[![ci](https://github.com/diohabara/ccc/actions/workflows/ci.yaml/badge.svg)](https://github.com/diohabara/ccc/actions/workflows/ci.yaml)

An experimental C compiler.

## how to develop

### dependencies

- `docker`

### build

```bash
docker build -t ccc - < Dockerfile
```

### help

```bash
docker run -v --platform=linux/amd64 "${PWD}:src" -w/src ccc make
```

### lint/format

```bash
docker run -v --platform=linux/amd64 "${PWD}:src" -w/src ccc make lint
```

### test

When you want to see if the compiler is working,

```bash
docker run -v --platform=linux/amd64 "${PWD}:src" -w/src ccc make test
```

When you debug something about the testing,

```bash
docker run -v --platform=linux/amd64 "${PWD}:src" -w/src ccc make debug
```

### clean

When you want to remove object files,

```bash
docker run -v --platform=linux/amd64 "${PWD}:src" -w/src ccc make clean
```

## references

- <https://www.sigbus.info/compilerbook>
- <https://github.com/rui314/chibicc>
- <https://github.com/rui314/chibicc/tree/reference>
