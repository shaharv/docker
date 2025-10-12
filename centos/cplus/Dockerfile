# Oracle Linux 7.9 C++ build docker image with GCC 11, LLVM 20, Python 3.14, CMake 3.31
# and OpenSSL 3.6.0. Based on glibc 2.17.
# Enable gcc by running the command: scl enable devtoolset-11 bash

FROM oraclelinux:7.9 AS builder

# Update system packages
RUN yum update -y

# Install GCC 11
RUN yum install -y oracle-softwarecollection-release-el7
RUN yum install -y devtoolset-11-gcc devtoolset-11-gcc-c++

# Install build tools and libraries
RUN yum install -y bzip2-devel libffi-devel git make nano perl-core tar wget xz zlib-devel

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
    ln -sf /opt/openssl/lib/libssl.so.3 /usr/lib/libssl.so && \
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
        make altinstall"
RUN ln -sf /opt/python/3.14.0/bin/python3.14 /usr/bin/python3 && \
    ln -sf /opt/python/3.14.0/bin/python3.14 /usr/bin/python
RUN python --version
RUN python -c "import ssl; print(ssl.OPENSSL_VERSION)"

# Build and install latest 3.X CMake from source
RUN wget https://github.com/Kitware/CMake/releases/download/v3.31.9/cmake-3.31.9.tar.gz && \
    tar -xf cmake-3.31.9.tar.gz
RUN scl enable devtoolset-11 "cd /cmake-3.31.9 && ./bootstrap --parallel=$(nproc --all) -- -DOPENSSL_ROOT_DIR=/opt/openssl"
RUN scl enable devtoolset-11 "cd /cmake-3.31.9 && make -j4 install"
RUN cmake --version

# Build and install LLVM 20 from source
RUN wget https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-20.1.0.tar.gz && \
    tar -xf llvmorg-20.1.0.tar.gz
RUN cd /llvm-project-llvmorg-20.1.0 && \
    scl enable devtoolset-11 "cmake -S llvm -B build -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release \
                              -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;lldb;lld'
                              -DCMAKE_INSTALL_PREFIX=/opt/llvm20 -DLLVM_TARGETS_TO_BUILD=X86"
RUN scl enable devtoolset-11 "cd /llvm-project-llvmorg-20.1.0/build && make -j4"
RUN scl enable devtoolset-11 "cd /llvm-project-llvmorg-20.1.0/build && make install"
RUN ln -sf /opt/llvm20/bin/clang        /usr/bin/clang && \
    ln -sf /opt/llvm20/bin/clang-tidy   /usr/bin/clang-tidy && \
    ln -sf /opt/llvm20/bin/clang-format /usr/bin/clang-format && \
    ln -sf /opt/llvm20/bin/ld.lld       /usr/bin/lld && \
    ln -sf /opt/llvm20/bin/lldb         /usr/bin/lldb
RUN clang --version
RUN clang-tidy --version
RUN clang-format --version
RUN lld --version
RUN lldb --version

# Print the glibc version
RUN getconf GNU_LIBPTHREAD_VERSION
