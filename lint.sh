#!/bin/bash
shellcheck ./*.sh
clang-format -i ./*.c