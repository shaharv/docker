# Ubuntu 22.04 C++ build docker image with
# CMake, GNU make, GCC 11, Clang 17, Python 3.10, IWYU and git.

FROM ubuntu:22.04

# Install basic packages
RUN apt update && apt install -y coreutils gnupg nano wget

# Install CMake (3.22.1)
RUN apt install -y cmake

# Install Python 3.10
RUN apt install -y python3 python3-pip

# Install CMake tools
RUN pip3 install cmakelang

# Install GNU make (4.3-4)
RUN apt install -y make

# Install GCC 10 (11.2.0)
RUN apt install -y gcc-10 g++-10

# Install Clang 17 (17.0.2)
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN echo 'deb http://apt.llvm.org/focal/ llvm-toolchain-focal-17 main' | tee -a /etc/apt/sources.list
RUN apt update && apt install -y clang-17 clang-format-17 clang-tidy-17
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 1700

# Install git
RUN apt install -y git

# Install include-what-you-use 0.21 (compatible with Clang 17)
RUN apt install -y libclang-17-dev && \
    ln -s /usr/bin/python3 /usr/bin/python && \
    git clone https://github.com/include-what-you-use/include-what-you-use.git /iwyu/iwyu && \
    cd /iwyu/iwyu && \
    git checkout clang_17 && \
    cd .. && \
    mkdir build && cd build && \
    cmake ../iwyu && \
    make -j install

CMD ["/bin/bash"]
