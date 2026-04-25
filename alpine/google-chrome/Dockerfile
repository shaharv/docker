# For running the image:
# XSOCK=/tmp/.X11-unix podman run -it --network=host -v $XSOCK:/tmp/.X11-unix -e DISPLAY alpine-google-chrome:3.23 /opt/google/chrome/chrome --no-sandbox

#
# Debug:
# - Add '--cap-add=SYS_PTRACE --security-opt seccomp=unconfined' for gdb and strace.
# - Debug crash before main: LD_DEBUG=all /opt/google/chrome/chrome
# - Debug chrome: gdb /opt/google/chrome/chrome
# - $gdb set disable-randomization on
#   $info file
#   b *<entry point>
#
FROM alpine:3.23

# Set up Alpine's glibc compatibility layer. Use gcompat as the loader so the
# Chrome binary and Alpine's musl-built dependencies stay on the same libc side.
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8
RUN set -ex && \
    apk --no-cache add ca-certificates curl gcompat libstdc++

COPY chrome-glibc-shim.c /tmp/chrome-glibc-shim.c
RUN set -ex && \
	apk add --no-cache --virtual .build-deps gcc musl-dev && \
	gcc -shared -fPIC -O2 -o /usr/local/lib/chrome-glibc-shim.so /tmp/chrome-glibc-shim.c && \
	apk del .build-deps && \
	rm /tmp/chrome-glibc-shim.c

# Install prerequisites and helper packages
RUN apk add --no-cache \
	bash dpkg font-noto xeyes
RUN printf '0123456789abcdef0123456789abcdef\n' > /etc/machine-id

# Download and unpack Chrome
RUN set -ex && \
	curl -SL https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb -o /google-chrome-stable_current_amd64.deb && \
	dpkg -x /google-chrome-stable_current_amd64.deb google-chrome-stable && \
	mv /google-chrome-stable/usr/bin/* /usr/bin && \
	mv /google-chrome-stable/usr/share/* /usr/share && \
	mv /google-chrome-stable/etc/* /etc && \
	mv /google-chrome-stable/opt/* /opt && \
	rm -r /google-chrome-stable /google-chrome-stable_current_amd64.deb

RUN set -ex && \
	apk add --no-cache --virtual .patch-deps patchelf && \
	cp /usr/local/lib/chrome-glibc-shim.so /opt/google/chrome/libchrome-glibc-shim.so && \
	patchelf --add-needed /opt/google/chrome/libchrome-glibc-shim.so /opt/google/chrome/chrome && \
	patchelf --add-needed /opt/google/chrome/libchrome-glibc-shim.so /opt/google/chrome/chrome_crashpad_handler && \
	apk del .patch-deps

# Install Chrome dependencies (updated package names for Alpine 3.23)
RUN apk add --no-cache --force-overwrite \
	alsa-lib \
	at-spi2-core \
	eudev-libs \
	expat \
	glib \
	gtk+3.0 \
	libdrm \
	libx11 \
	libxcomposite \
	libxcursor \
	libxdamage \
	libxext \
	libxi \
	libxrandr \
	libxscrnsaver \
	libxshmfence \
	libxtst \
	mesa-gbm \
	nss \
	pango

RUN set -ex && \
	adduser -D -s /bin/sh chrome

USER chrome
WORKDIR /home/chrome
