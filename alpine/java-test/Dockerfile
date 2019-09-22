# The all-in-one Java testing docker.
#
# Building the image: 'docker image build --squash -t java-test-all'.
#
# Using the image:
# - For gdb debugging, start docker with '--cap-add=SYS_PTRACE --security-opt seccomp=unconfined'.
# - For exposing all ports, add '--network="host'.
#

FROM alpine:3.9

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash binutils coreutils file grep nano procps strace sudo tar unzip

# Install packaged OpenJDK 8
RUN apk --no-cache add openjdk8

# Install gradle
RUN apk --no-cache add gradle

# Install OpenJDK 7
RUN apk --no-cache add openjdk7

# Install OpenJDK 9, 10 and 11
RUN apk --no-cache add openjdk9 openjdk10 openjdk11 --repository=http://dl-cdn.alpinelinux.org/alpine/edge/community

# Install patched gdb for OpenJDK debugging
RUN set -ex && \
	apk add --no-cache gdb python2 && \
	mkdir -p /temp && cd /temp && \
	wget https://github.com/shaharv/alpine-gdb-builds/releases/download/v0.1/gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	unzip gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	cd gdb-8.3.50.20190410-git_x86-64_musl && \
	cp -a bin share /usr && \
	rm -rf /temp

# Download OpenJDK 8 versions
RUN set -ex && \
	cd /usr/lib/jvm && \
        for JAVA_VER in 8.131.11-r2 8.151.12-r0 8.171.11-r0 8.181.13-r0 8.191.12-r0 8.201.08-r0 8.201.08-r1 8.212.04-r0 8.222.10-r1; \
	do \
		ZIP_NAME=java-1.8-openjdk-$JAVA_VER.tar.gz && \
		wget https://github.com/shaharv/alpine-openjdk-builds/releases/download/1.8/$ZIP_NAME && \
		tar -xf $ZIP_NAME && \
		rm $ZIP_NAME; \
	done

# Download Azul Zulu OpenJDK 11
RUN set -ex && \
	cd /usr/lib/jvm && \
	ZIP_NAME=zulu11.31.11-ca-jdk11.0.3-linux_musl_x64.tar.gz && \
	wget https://cdn.azul.com/zulu/bin/$ZIP_NAME && \
	tar -xf $ZIP_NAME && \
	rm $ZIP_NAME

# OverOps env.
ENV TAKIPI_COLLECTOR_HOST=localhost
ENV TAKIPI_COLLECTOR_PORT=6060

CMD ["/bin/bash"]
