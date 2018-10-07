FROM alpine:3.2

ENV LANG C.UTF-8

# Install build tools
RUN set -ex \
	&& apk --no-cache add \
		cmake coreutils gcc g++ git make

# Install useful packages
RUN set -ex \
	&& apk --no-cache add \
		bash file nano

# Install OpenJDK 7
RUN set -ex \
	&& apk --no-cache add \
		openjdk7
