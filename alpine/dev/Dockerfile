# Alpine 3.22 C++/Java Developer Image
#
# For IntelliJ and GUI (X11), run the image with:
# $ XSOCK=/tmp/.X11-unix && sudo docker run -i -v $XSOCK:$XSOCK -e DISPLAY -u developer -t [image-name]
#
# Then run IntelliJ with:
# LD_PRELOAD=/usr/lib/libjemalloc.so.2 /idea-IC-251.28774.11/bin/idea.sh

FROM alpine:3.22

ENV IDEA_VER 2025.1.6
ENV IDEA_BUILD 251.28774.11

# Install required packages
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

# Install C++ build tools
RUN set -ex && \
	apk --no-cache --update add cmake g++ git linux-headers make

# Install Java tools
RUN set -ex && \
	apk --no-cache --update add gradle openjdk21

# Set timezone (default = UTC)
ENV TZ US/Eastern
RUN set -ex && \
	apk add tzdata && \
	cp /usr/share/zoneinfo/$TZ /etc/localtime && \
	echo "$TZ" > /etc/timezone && \
	date

# Install IntelliJ Community.
# Use Alpine Java from package instead of the bundled glibc-compatible Java.
# Setting IDEA_JDK alone isn't enough for IntelliJ to complete the startup process.
RUN set -ex && \
	wget https://download-cf.jetbrains.com/idea/ideaIC-${IDEA_VER}.tar.gz && \
	tar -xf ideaIC-${IDEA_VER}.tar.gz && \
	rm ideaIC-${IDEA_VER}.tar.gz

# Create a new user with no password
ENV USERNAME developer
RUN set -ex && \
	useradd --create-home --key MAIL_DIR=/dev/null --shell /bin/bash ${USERNAME} && \
	passwd -d ${USERNAME} && \
	chmod 777 -R /home/${USERNAME} && \
	echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN mv /idea-IC-${IDEA_BUILD}/jbr /idea-IC-${IDEA_BUILD}/jbr_old
RUN ln -s /usr/lib/jvm/java-21-openjdk /idea-IC-${IDEA_BUILD}/jbr
RUN chown -R developer /idea-IC-${IDEA_BUILD}

# Install extra packages for Idea on Alpine:
# - libc6-compat for installing a /lib/ld-linux-x86-64.so.2 symlink that is picked by fsnotifier
# - jemalloc for avoiding malloc_trim not found error
RUN set -ex && \
        apk --no-cache --update add libc6-compat jemalloc

USER developer

# Set environment variables
ENV LD_PRELOAD /usr/lib/libjemalloc.so.2
ENV JAVA_HOME  /usr/lib/jvm/java-21-openjdk
ENV JDK_HOME   /usr/lib/jvm/java-21-openjdk
ENV IDEA_JDK   /usr/lib/jvm/java-21-openjdk

ENTRYPOINT /bin/bash
