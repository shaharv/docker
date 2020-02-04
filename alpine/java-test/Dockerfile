# The all-in-one Java testing docker.
#
# Building the image: 'docker image build --squash -t java-test-all .'.
#
# Using the image:
# - For gdb debugging, start docker with '--cap-add=SYS_PTRACE --security-opt seccomp=unconfined'.
# - For exposing all ports, add '--network="host'.
#

FROM alpine:3.11

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash binutils coreutils file grep nano procps strace sudo tar unzip

# Install packaged OpenJDK builds with debug symbols
RUN apk --no-cache add \
	openjdk7 \
	openjdk8 \
	openjdk8-dbg \
	openjdk9 \
	openjdk9-dbg \
	openjdk10 \
	openjdk10-dbg \
	openjdk11 \
	openjdk11-dbg

# Install experimental OpenJDK builds from edge
RUN apk --no-cache --repository=http://dl-cdn.alpinelinux.org/alpine/edge/testing add \
	openjdk12 \
	openjdk12-dbg

# Install gradle
RUN apk --no-cache add gradle

# Install patched gdb for OpenJDK debugging
RUN set -ex && \
	apk add --no-cache gdb python2 && \
	mkdir -p /temp && cd /temp && \
	wget https://github.com/shaharv/alpine-gdb-builds/releases/download/v0.1/gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	unzip gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	cd gdb-8.3.50.20190410-git_x86-64_musl && \
	cp -a bin share /usr && \
	rm -rf /temp

# Download Azul Zulu OpenJDK 11
RUN set -ex && \
	cd /usr/lib/jvm && \
	ZIP_NAME=zulu11.37.17-ca-jdk11.0.6-linux_musl_x64.tar.gz && \
	wget https://cdn.azul.com/zulu/bin/$ZIP_NAME && \
	tar -xf $ZIP_NAME && \
	rm $ZIP_NAME

# OverOps env.
ENV TAKIPI_COLLECTOR_HOST=localhost
ENV TAKIPI_COLLECTOR_PORT=6060

CMD ["/bin/bash"]
