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

# Build onnxruntime. Tests are disabled in this phase to prevent failing tests from failing the entire build.
#
RUN cd /onnxruntime && ./build.sh --config Release --parallel --build_wheel --skip_tests --cmake_extra_defines CMAKE_CXX_FLAGS=-Wno-deprecated-copy

# Run onnxruntime tests
#
RUN cd /onnxruntime && ./build.sh --config Release --parallel --test

