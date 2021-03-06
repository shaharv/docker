FROM alpine:3.11

# Set up glibc
#
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8
ENV GLIBC_REPO=https://github.com/sgerrand/alpine-pkg-glibc
ENV GLIBC_VERSION=2.30-r0
RUN set -ex && \
    apk --update add libstdc++ curl ca-certificates && \
    for pkg in glibc-${GLIBC_VERSION} glibc-bin-${GLIBC_VERSION}; \
        do curl -sSL ${GLIBC_REPO}/releases/download/${GLIBC_VERSION}/${pkg}.apk -o /tmp/${pkg}.apk; done && \
    apk add --allow-untrusted /tmp/*.apk && \
    rm -v /tmp/*.apk && \
    /usr/glibc-compat/sbin/ldconfig /lib /usr/glibc-compat/lib

# Install prerequisites
#
RUN apk add --no-cache \
	bash dpkg

# Download and unpack Chrome
RUN set -ex && \
	curl -SL https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb -o /google-chrome-stable_current_amd64.deb && \
	dpkg -x /google-chrome-stable_current_amd64.deb google-chrome-stable && \
	mv /google-chrome-stable/usr/bin/* /usr/bin && \
	mv /google-chrome-stable/usr/share/* /usr/share && \
	mv /google-chrome-stable/etc/* /etc && \
	mv /google-chrome-stable/opt/* /opt && \
	rm -r /google-chrome-stable

# Install Chrome dependencies
RUN apk add --no-cache \
	alsa-lib \
	atk \
	at-spi2-atk \
	expat \
	glib \
	gtk+3.0 \
	libx11 \
	libxcomposite \
	libxcursor \
	libxdamage \
	libxext \
	libxi \
	libxrandr \
	libxscrnsaver \
	libxtst \
	nss \
	pango

