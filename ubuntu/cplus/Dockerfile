# Ubuntu 20.04 C++ build docker image with
# CMake, GNU make, GCC 10, Clang 12 and Clang 15.

FROM ubuntu:20.04

RUN apt update 

# Install CMake (13.6.3)
RUN apt install -y --no-install-recommends cmake

# Install GNU make (4.2.1)
RUN apt install -y make

# Install GCC 10 (10.3.0)
RUN apt install -y --no-install-recommends gcc-10 g++-10

# Install Clang 12 (12.0.0), including Python 3 (3.8.10)
RUN apt install -y clang-12

# Install Clang 15 (15.0.2)
RUN apt install -y --no-install-recommends software-properties-common
RUN apt install -y wget gnupg
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN add-apt-repository 'deb http://apt.llvm.org/focal/ llvm-toolchain-focal-15 main' && apt update
RUN apt install -y clang-15

CMD ["/bin/bash"]
