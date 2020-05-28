FROM alpine:3.11 AS BUILDER

# Install build dependencies
RUN apk add --update --no-cache --virtual .build-deps \
    ninja cmake g++ python3

# Get zapcc source code
RUN wget https://github.com/yrnkrn/zapcc/archive/master.zip -O /zapcc.zip && \
    mkdir /zapcc && \
    unzip zapcc.zip -d /zapcc && \
    mv /zapcc/zapcc-master /zapcc/llvm && \
    rm /zapcc.zip

# Build zapcc
RUN mkdir /zapcc/build && cd /zapcc/build && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_WARNINGS=OFF ../llvm && \
    ninja install

FROM alpine:3.11

# Copy zapcc files
COPY --from=builder /usr/local/bin/zapcc         /usr/local/bin/
COPY --from=builder /usr/local/bin/zapccs        /usr/local/bin/
COPY --from=builder /usr/local/bin/zapccs.config /usr/local/bin/

# Copy llvm/clang files
COPY --from=builder /usr/local/bin/*clang*       /usr/local/bin/
COPY --from=builder /usr/local/bin/*llvm*        /usr/local/bin/
COPY --from=builder /usr/local/include/clang     /usr/local/include/
COPY --from=builder /usr/local/include/llvm      /usr/local/include/
COPY --from=builder /usr/local/include/llvm-c    /usr/local/include/
COPY --from=builder /usr/local/lib/*LLVM*        /usr/local/lib/
COPY --from=builder /usr/local/lib/*clang*       /usr/local/lib/
COPY --from=builder /usr/local/share/clang/      /usr/local/share/

# Install required packages
RUN apk update && \
    apk add libstdc++ musl-dev
