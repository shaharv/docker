FROM alpine:3.8

ENV LANG C.UTF-8

RUN set -ex && \
	apk --no-cache --update add \
	# basic packages
		bash bash-completion coreutils file grep openssl openssh nano sudo tar xz \
	# debug tools
		gdb musl-dbg strace \
	# X11 and user utils
		libxext-dev libxrender-dev libxtst-dev shadow xauth xhost \
	# Docs and man
		man man-pages less less-doc \
	# GUI fonts
		font-noto

RUN set -ex && \
	apk --no-cache --update add \
	# C++ build tools
		cmake g++ git linux-headers libpthread-stubs make

RUN set -ex && \
	apk --no-cache --update add \
	# Java tools
		gradle openjdk8 openjdk8-dbg

# Install IntelliJ Community
RUN set -ex && \
	wget https://download-cf.jetbrains.com/idea/ideaIC-2018.2.4.tar.gz && \
	tar -xf ideaIC-2018.2.4.tar.gz && \
	rm ideaIC-2018.2.4.tar.gz

# Create a new user with no password
RUN set -ex && \
	useradd --create-home --key MAIL_DIR=/dev/null --shell /bin/bash developer && \
	passwd -d developer

# Set additional environment variables
ENV JAVA_HOME /usr/lib/jvm/java-1.7-openjdk
ENV JDK_HOME  /usr/lib/jvm/java-1.7-openjdk
ENV JAVA_EXE  /usr/lib/jvm/java-1.7-openjdk/bin/java
