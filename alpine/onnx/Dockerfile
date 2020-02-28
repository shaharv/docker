FROM alpine:3.11 AS Builder

ENV ONNXRUNTIME_TAG v1.1.2

# Install build tools
#
RUN apk add --no-cache \
    bash cmake gcc g++ git make python3-dev

# Install headers and libs
#
RUN apk add --no-cache \
    lapack-dev libexecinfo-dev linux-headers openblas-dev zlib-dev

# Symlink /usr/bin/python to python3
#
RUN ln -s /usr/bin/python3 /usr/bin/python

# Install python modules
#
RUN pip3 install --upgrade pip && \
    pip3 install cython numpy pybind11 wheel

# Install pre-3.11 protobuf for onnx, due to https://github.com/onnx/onnx/issues/2481
#
RUN apk add --no-cache \
    protobuf-dev=3.6.1-r1 --repository=http://dl-cdn.alpinelinux.org/alpine/v3.10/main

# Install pre-1.4.0 scipy for onnxmltools, due to https://github.com/scipy/scipy/issues/11319
#
RUN pip3 install scipy==1.2.3

# Install onnx and onnxmltools
#
RUN pip3 install onnx onnxmltools

# Clone onnxruntime
#
RUN git clone --branch $ONNXRUNTIME_TAG --recursive https://github.com/Microsoft/onnxruntime

# Remove Alpine failing test ContribOpTest.StringNormalizerTest, unsupported due to
# missing musl locale functionality
#
RUN rm /onnxruntime/onnxruntime/test/providers/cpu/nn/string_normalizer_test.cc

# Build and test onnxruntime
#
RUN cd /onnxruntime && ./build.sh --config Release --parallel --build_wheel --cmake_extra_defines CMAKE_CXX_FLAGS=-Wno-deprecated-copy

