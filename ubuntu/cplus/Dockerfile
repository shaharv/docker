# Ubuntu 24.04 C++ build docker image with
# CMake, GNU make, GCC 13, Clang 20, Python 3.12, IWYU and git.

FROM ubuntu:24.04

# Install basic packages
RUN apt update && apt install -y coreutils gnupg nano wget

# Install CMake (3.28.3)
RUN apt install -y cmake

# Install Python 3.12
RUN apt install -y python3 python3-pip python3-venv

# Install GNU make (4.3)
RUN apt install -y make

# Install GCC 13 (13.3.0)
RUN apt install -y gcc-13 g++-13

# Install Clang 20 (20.1.2)
RUN apt update && apt install -y clang-20 clang-format-20 clang-tidy-20
RUN update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-20 2000

# Install git
RUN apt install -y git

# Install include-what-you-use 0.24 (compatible with Clang 20)
RUN apt install -y libclang-20-dev && \
    ln -s /usr/bin/python3 /usr/bin/python && \
    git clone https://github.com/include-what-you-use/include-what-you-use.git /iwyu/iwyu && \
    cd /iwyu/iwyu && \
    git checkout 0.24 && \
    cd .. && \
    mkdir build && cd build && \
    cmake ../iwyu && \
    make -j install

CMD ["/bin/bash"]
