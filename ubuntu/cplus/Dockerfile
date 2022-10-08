# Ubuntu 20.04 C++ build docker image with
# CMake, GNU make, GCC 10, Clang 12, Clang 15, Python 3.8, IWYU and git.

FROM ubuntu:20.04

# Install basic packages
RUN apt update && apt install -y coreutils gnupg nano wget

# Install CMake (13.6.3)
RUN apt install -y cmake

# Install Python 3.8
RUN apt install -y python3 python3-pip

# Install CMake tools
RUN pip3 install cmakelang

# Install GNU make (4.2.1)
RUN apt install -y make

# Install GCC 10 (10.3.0)
RUN apt install -y gcc-10 g++-10

# Install Clang 12 (12.0.0), including Python 3 (3.8.10)
RUN apt install -y clang-12

# Install Clang 15 (15.0.2)
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo 'deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main' | tee -a /etc/apt/sources.list
RUN apt update && apt install -y clang-15 clang-format-15 clang-tidy-15
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 1500

# Install git
RUN apt install -y git

# Install include-what-you-use 0.16 (compatible with Clang 12)
RUN apt install -y libclang-12-dev && \
    ln -s /usr/bin/python3 /usr/bin/python && \
    git clone https://github.com/include-what-you-use/include-what-you-use.git /iwyu/iwyu && \
    cd /iwyu/iwyu && \
    git checkout clang_12 && \
    cd .. && \
    mkdir build && cd build && \
    cmake -DIWYU_LLVM_ROOT_PATH=/usr/lib/llvm-12 ../iwyu && \
    make -j install

CMD ["/bin/bash"]
