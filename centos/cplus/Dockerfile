# Oracle Linux 7.9 C++ build docker image. With glibc 2.17.
# Enable gcc by running the command: scl enable devtoolset-10 bash

FROM oraclelinux:7.9

# Update system packages
RUN yum update -y

# Install GCC 10
RUN yum install -y oracle-softwarecollection-release-el7
RUN yum install -y devtoolset-10-gcc devtoolset-10-gcc-c++

# Print the glibc version
RUN getconf GNU_LIBPTHREAD_VERSION
