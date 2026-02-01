# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a Docker utilities repository containing curated Dockerfile configurations for various development environments. The images focus on C++ development, Java testing, Python environments, and specialized tools like ONNX Runtime and compiler toolchains.

## Build Commands

Build individual images using standard Docker commands with optional `--squash` for smaller images:

```bash
# General pattern
docker image build -t <image-name> <path-to-dockerfile-dir>

# Examples from the repository
docker image build --squash -t onnxruntime-alpine alpine/onnxruntime/
docker image build --squash -t java-test-all alpine/java-test/
docker image build --squash -t java-8-test alpine/java-8-test/
```

## Repository Structure

- **alpine/** - Alpine Linux based images (lightweight)
  - `cplus/` - C++ development and debug base image
  - `dev/` - Full IntelliJ IDEA IDE with C++/Java dev tools
  - `glibc/` - glibc compatibility layer for Alpine
  - `google-chrome/` - Chrome browser with debugging support
  - `java-8-test/`, `java-test/` - Multi-version Java testing environments
  - `onnxruntime/` - ONNX Runtime ML framework
  - `zapcc/` - Zapcc C++ compiler

- **centos/** - Enterprise Linux based images
  - `cplus/` - Oracle Linux 7.9 with GCC 11, LLVM 20, Python 3.14, CMake 3.31

- **ubuntu/** - Ubuntu based images
  - `cplus/` - Ubuntu 24.04 with GCC 13, Clang 20, Python 3.12, IWYU

## Dockerfile Conventions

- **Multi-stage builds**: Used in centos/cplus, alpine/zapcc, and alpine/onnxruntime to separate build artifacts from runtime and minimize final image size
- **Package installation**: Use `apk add --no-cache` for Alpine, `apt install` for Ubuntu
- **Grouped RUN commands**: Batch complex operations together for layer optimization
- **Symlink creation**: Create /usr/bin symlinks to compiler toolchains (e.g., `clang++` -> `clang++-20`)
- **Version pinning**: Document specific versions in comments
- **Debug support**: Include gdb, strace, and debugging symbols where needed

## Running Containers

Debug containers (for gdb support):
```bash
docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined <image>
```

GUI applications (X11 forwarding):
```bash
XSOCK=/tmp/.X11-unix
docker run -i -v $XSOCK:$XSOCK -e DISPLAY <image>
```

IntelliJ with memory optimization:
```bash
docker run -e LD_PRELOAD=/usr/lib/libjemalloc.so.2 ...
```
