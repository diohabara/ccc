FROM --platform=linux/amd64 ubuntu:22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install --no-install-recommends \
  binutils \
  clang-format \
  gcc \
  gdb \
  git \
  libc6-dev \
  make \
  shellcheck \
  shfmt \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
