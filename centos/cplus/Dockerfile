# Oracle Linux 7.9 C++ build docker image. With glibc 2.17.
# Enable gcc by running the command: scl enable devtoolset-11 bash

FROM oraclelinux:7.9

# Update system packages
RUN yum update -y

# Install GCC 11
RUN yum install -y oracle-softwarecollection-release-el7
RUN yum install -y devtoolset-11-gcc devtoolset-11-gcc-c++

# Install Python 3 and build utils
RUN yum install -y make openssl-devel python3 wget tar xz

# Build and install CMake from source
RUN wget https://github.com/Kitware/CMake/releases/download/v3.31.9/cmake-3.31.9.tar.gz && \
    tar -xf cmake-3.31.9.tar.gz && \
    scl enable devtoolset-11 "cd /cmake-3.31.9 && ./bootstrap --parallel=$(nproc --all)"
RUN scl enable devtoolset-11 "cd /cmake-3.31.9 && make -j4 install"
RUN cmake --version

# Build and install LLVM 20 from source
RUN wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-20.1.0.tar.gz && \
    tar -xf llvmorg-20.1.0.tar.gz
RUN cd /llvm-project-llvmorg-20.1.0 && \
    scl enable devtoolset-11 "cmake -S llvm -B build -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;lldb;lld'"

# Print the glibc version
RUN getconf GNU_LIBPTHREAD_VERSION
