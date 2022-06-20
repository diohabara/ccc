# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.234.0/containers/ubuntu/.devcontainer/base.Dockerfile
# [Choice] Ubuntu version (use ubuntu-22.04 or ubuntu-18.04 on local arm64/Apple Silicon): ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
FROM --platform=linux/amd64 ubuntu:22.04

# [Optional] Uncomment this section to install additional OS packages.
RUN apt update
RUN export DEBIAN_FRONTEND=noninteractive
RUN apt-get -y install --no-install-recommends gcc make git binutils libc6-dev clang-format shellcheck
RUN apt upgrade -y
