#!/bin/bash
clang-format -i ./*.c
clang-format -i ./*.h
shfmt -f . | shellcheck
shfmt -f . | xargs shfmt -w
