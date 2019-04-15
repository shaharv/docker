FROM alpine:3.8

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash coreutils file nano

# Install OpenJDK packages
RUN set -ex && \
	VER=8.201.08-r0 && \
	apk --no-cache add \
		openjdk8=$VER openjdk8-jre-base=$VER openjdk8-jre-lib=$VER openjdk8-jre=$VER openjdk8-dbg=$VER

CMD ["/bin/bash"]
