FROM alpine:3.11 AS Builder

# Install build tools
#
RUN apk add --no-cache \
    bash cmake gcc g++ git make python3-dev

# Install headers and libs
#
RUN apk add --no-cache \
    libexecinfo-dev linux-headers zlib-dev

# Install python modules
#
RUN pip3 install --upgrade pip && \
    pip3 install numpy wheel

# Clone onnxruntime
#
RUN git clone --recursive https://github.com/Microsoft/onnxruntime

# Remove Alpine failing test ContribOpTest.StringNormalizerTest, unsupported due to
# missing musl locale functionality
#
RUN rm /onnxruntime/onnxruntime/test/providers/cpu/nn/string_normalizer_test.cc

# Build and test onnxruntime
#
RUN cd /onnxruntime && ./build.sh --config Release --parallel --build_wheel --cmake_extra_defines CMAKE_CXX_FLAGS=-Wno-deprecated-copy

