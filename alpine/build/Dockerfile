FROM alpine:3.8

ENV LANG C.UTF-8

# Install build tools
RUN set -ex \
	&& apk --no-cache add \
		binutils cmake coreutils g++ git make

# Install useful packages
RUN set -ex \
	&& apk --no-cache add \
		bash file nano

# Install OpenJDK 8
RUN set -ex \
	&& apk --no-cache add \
		openjdk8
