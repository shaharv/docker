# Alpine 3.22 C++/Java Developer Image
#
# For IntelliJ and GUI (X11), run the image with:
# $ XSOCK=/tmp/.X11-unix && sudo docker run -i -v $XSOCK:$XSOCK -e DISPLAY -u developer -t [image-name]
#
# Then run IntelliJ with:
# /idea-IC-252.23892.409/bin/idea.sh

FROM alpine:3.22

RUN set -ex && \
	apk --no-cache --update add \
	# basic packages
		bash bash-completion coreutils file grep openssl openssh nano sudo tar xz \
	# debug tools
		binutils gdb musl-dbg strace \
	# docs and man
		bash-doc man-db man-pages less less-doc \
	# GUI fonts
		font-noto \
	# user utils
		shadow

RUN set -ex && \
	apk --no-cache --update add \
	# C++ build tools
		cmake g++ git linux-headers make

RUN set -ex && \
	apk --no-cache --update add \
	# Java tools
		gradle openjdk21

# Install IntelliJ Community
RUN set -ex && \
        wget https://download-cf.jetbrains.com/idea/ideaIC-2025.2.tar.gz && \
        tar -xf ideaIC-2025.2.tar.gz && \
        rm ideaIC-2025.2.tar.gz

# Create a new user with no password
ENV USERNAME developer
RUN set -ex && \
	useradd --create-home --key MAIL_DIR=/dev/null --shell /bin/bash $USERNAME && \
	passwd -d $USERNAME

# Set timezone (default = UTC)
ENV TZ US/Eastern
RUN set -ex && \
	apk add tzdata && \
	cp /usr/share/zoneinfo/$TZ /etc/localtime && \
	echo "$TZ" > /etc/timezone && \
	date

# Set additional environment variables
ENV JAVA_HOME /usr/lib/jvm/java-21-openjdk
ENV JDK_HOME  /usr/lib/jvm/java-21-openjdk
ENV JAVA_EXE  /usr/lib/jvm/java-21-openjdk/bin/java
ENV IDEA_JDK  /usr/lib/jvm/java-21-openjdk/bin/java
