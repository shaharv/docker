# Alpine 3.22 C++/Java Developer Image
#
# For IntelliJ and GUI (X11), run the image with:
# $ XSOCK=/tmp/.X11-unix && sudo docker run -i -v $XSOCK:$XSOCK -e DISPLAY -u developer -t [image-name]
#
# Then run IntelliJ with:
# /idea-IC-${IDEA_BUILD}/bin/idea.sh

FROM alpine:3.22

ENV IDEA_VER 2025.2.2
ENV IDEA_BUILD 252.26199.169

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

# Set timezone (default = UTC)
ENV TZ US/Eastern
RUN set -ex && \
	apk add tzdata && \
	cp /usr/share/zoneinfo/$TZ /etc/localtime && \
	echo "$TZ" > /etc/timezone && \
	date

# Create a new user with no password
ENV USERNAME developer
RUN set -ex && \
	useradd --create-home --key MAIL_DIR=/dev/null --shell /bin/bash $USERNAME && \
	passwd -d $USERNAME

# Install IntelliJ Community.
# Use Alpine Java from package instead of the bundled glibc-compatible Java.
# Setting IDEA_JDK alone isn't enough for IntelliJ to complete the startup process.
RUN set -ex && \
	wget https://download-cf.jetbrains.com/idea/ideaIC-${IDEA_VER}.tar.gz && \
	tar -xf ideaIC-${IDEA_VER}.tar.gz && \
	rm ideaIC-${IDEA_VER}.tar.gz

RUN mv /idea-IC-${IDEA_BUILD}/jbr /idea-IC-${IDEA_BUILD}/jbr_old
RUN ln -s /usr/lib/jvm/java-21-openjdk /idea-IC-${IDEA_BUILD}/jbr
RUN chown -R developer /idea-IC-${IDEA_BUILD}

USER developer

# Set additional environment variables
ENV JAVA_HOME /usr/lib/jvm/java-21-openjdk
ENV JDK_HOME  /usr/lib/jvm/java-21-openjdk
ENV IDEA_JDK  /usr/lib/jvm/java-21-openjdk
