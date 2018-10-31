FROM alpine:3.8

ENV LANG C.UTF-8

# Install useful packages
RUN set -ex \
	&& apk --no-cache add \
		bash coreutils file nano

# Install OpenJDK
RUN set -ex \
	&& apk --no-cache add \
		openjdk7 openjdk8 openjdk8-dbg
