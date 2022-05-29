#!/bin/bash
shellcheck ./*.sh
clang-format -i ./*.c
clang-format -i ./*.h