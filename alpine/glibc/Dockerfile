# Credit: https://github.com/anapsix/docker-alpine-java

FROM alpine:3.23

ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

ENV GLIBC_REPO=https://github.com/sgerrand/alpine-pkg-glibc
ENV GLIBC_VERSION=2.35-r1

RUN set -ex && \
    apk --update add libstdc++ curl ca-certificates && \
    for pkg in glibc-${GLIBC_VERSION} glibc-bin-${GLIBC_VERSION}; \
        do curl -sSL ${GLIBC_REPO}/releases/download/${GLIBC_VERSION}/${pkg}.apk -o /tmp/${pkg}.apk; done && \
    apk add --allow-untrusted --force-overwrite /tmp/*.apk && \
    rm -v /tmp/*.apk && \
    ln -sf /usr/glibc-compat/lib/ld-linux-x86-64.so.2 /lib/ld-linux-x86-64.so.2 && \
    /usr/glibc-compat/sbin/ldconfig /lib /usr/glibc-compat/lib

# Test: download a glibc-linked binary (GNU hello from Ubuntu, needs only GLIBC_2.2.5/2.4) and verify it runs
RUN set -ex && \
    apk add --no-cache binutils && \
    curl -sSL http://archive.ubuntu.com/ubuntu/pool/main/h/hello/hello_2.10-1_amd64.deb -o /tmp/hello.deb && \
    mkdir /tmp/hello-pkg && \
    cd /tmp/hello-pkg && \
    ar x /tmp/hello.deb && \
    tar xf data.tar.* && \
    /tmp/hello-pkg/usr/bin/hello | grep -q 'Hello, world!' && \
    readelf -p .interp /tmp/hello-pkg/usr/bin/hello | grep -q '/lib64/ld-linux-x86-64.so.2' && \
    readlink -f /lib/ld-linux-x86-64.so.2 | grep -q '/usr/glibc-compat/' && \
    echo "Verified: loader resolves to sgerrand glibc" && \
    rm -rf /tmp/hello.deb /tmp/hello-pkg && \
    apk del binutils
