FROM alpine:3.8

ENV LANG C.UTF-8

RUN set -ex \
	&& apk update

# Install basic packages
RUN set -ex && \
	apk --no-cache add \
		bash coreutils file grep openssl openssh nano tar xz

# Install build tools
RUN set -ex && \
	apk --no-cache add \
		cmake g++ git linux-headers libpthread-stubs make

# Install debug tools
RUN set -ex && \
	apk --no-cache add \
		gdb musl-dbg strace

# Install X11 and user utils
RUN set -ex && \
	apk --no-cache add \
		libxext-dev libxrender-dev libxtst-dev shadow xauth xhost

# Install Java tools
RUN set -ex && \
	apk --no-cache add \
		gradle openjdk8 openjdk8-dbg

# Install IntelliJ Community
RUN set -ex && \
	wget https://download-cf.jetbrains.com/idea/ideaIC-2018.2.4.tar.gz && \
	tar -xf ideaIC-2018.2.4.tar.gz && \
	rm ideaIC-2018.2.4.tar.gz

# Create a new user
RUN set -ex && \
	useradd --create-home --key MAIL_DIR=/dev/null --shell /bin/bash developer

# Set additional environment variables
ENV JAVA_HOME /usr/lib/jvm/java-1.7-openjdk
ENV JDK_HOME  /usr/lib/jvm/java-1.7-openjdk
ENV JAVA_EXE  /usr/lib/jvm/java-1.7-openjdk/bin/java
