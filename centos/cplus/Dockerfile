# Oracle Linux 7.9 C++ build docker image. With glibc 2.17.
# Enable gcc by running the command: scl enable devtoolset-11 bash

FROM oraclelinux:7.9 AS builder

# Update system packages
RUN yum update -y

# Install GCC 11
RUN yum install -y oracle-softwarecollection-release-el7
RUN yum install -y devtoolset-11-gcc devtoolset-11-gcc-c++

# Install build tools and libraries
RUN yum install -y bzip2-devel libffi-devel make openssl-devel perl-core tar wget xz zlib-devel

# Build and install OpenSSL from source (recent version required for Python build)
RUN wget https://github.com/openssl/openssl/archive/refs/tags/openssl-3.6.0.tar.gz && \
    tar -xf openssl-3.6.0.tar.gz && \
    cd /openssl-openssl-3.6.0 && \
    scl enable devtoolset-11 "./Configure --prefix=/opt/openssl no-docs no-tests" && \
    scl enable devtoolset-11 "make -j4 && make install"
RUN ln -sf /opt/openssl/lib64/libssl.so.3 /usr/lib64/libssl.so && \
    ln -sf /opt/openssl/lib64/libssl.so.3 /usr/lib64/libssl.so.3 && \
    ln -sf /opt/openssl/lib64/libcrypto.so.3 /usr/lib64/libcrypto.so.3 && \
    ln -sf /opt/openssl/lib/libssl.so.3 /usr/lib/libssl.so.3 && \
    ln -sf /opt/openssl/lib/libcrypto.so.3 /usr/lib/libcrypto.so.3 && \
    ln -sf /opt/openssl/lib64 /opt/openssl/lib

# Build and install Python 3 from source (3.8 or later required for LLVM)
RUN wget https://www.python.org/ftp/python/3.14.0/Python-3.14.0.tar.xz && \
    tar -xf Python-3.14.0.tar.xz && \
    cd /Python-3.14.0 && \
    scl enable devtoolset-11 " \
        LDFLAGS=-I/opt/openssl/include \
        CPPFLAGS=-L/opt/openssl/lib64 \
        LD_LIBRARY_PATH=/opt/openssl/lib64 \
        PKG_CONFIG_PATH=/opt/openssl/lib64/pkgconfig \
        ./configure --prefix=/opt/python/3.14.0 --with-openssl=/opt/openssl --enable-optimizations && \
        make -j4 && \
        make altinstall || true"
RUN python --version

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
