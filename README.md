# ccc

[![ci](https://github.com/diohabara/ccc/actions/workflows/ci.yaml/badge.svg)](https://github.com/diohabara/ccc/actions/workflows/ci.yaml)

An experimental C compiler.

## how to develop

You are supposed to work on this repo on the [`devcontainer`](https://code.visualstudio.com/docs/remote/containers) environment.

### lint/format

```bash
make lint
```

### test

When you want to see if the compiler is working,

```bash
make test
```

When you debug something about the testing,

```bash
make debug
```

## references

- <https://www.sigbus.info/compilerbook>
- <https://github.com/rui314/chibicc>
- <https://github.com/rui314/chibicc/tree/reference>
