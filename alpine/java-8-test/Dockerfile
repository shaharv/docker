# Java 8 testing docker image.
#
# Building the image: 'docker image build --squash -t java-test-8 .'.
#

FROM alpine:3.11

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash binutils coreutils file grep nano procps strace sudo tar unzip

# Install packaged OpenJDK 8
RUN apk --no-cache add openjdk8

# Install gradle
RUN apk --no-cache add gradle

# Download zipped OpenJDK 8 versions
RUN set -ex && \
	cd /usr/lib/jvm && \
        for JAVA_VER in 8.131.11-r2 8.151.12-r0 8.171.11-r0 8.181.13-r0 8.191.12-r0 8.201.08-r0 8.201.08-r1 8.212.04-r0 8.222.10-r1 8.232.09-r0; \
	do \
		ZIP_NAME=java-1.8-openjdk-$JAVA_VER.tar.gz && \
		wget https://github.com/shaharv/alpine-openjdk-builds/releases/download/1.8/$ZIP_NAME && \
		tar -xf $ZIP_NAME && \
		rm $ZIP_NAME; \
	done

# OverOps env.
ENV TAKIPI_COLLECTOR_HOST=localhost
ENV TAKIPI_COLLECTOR_PORT=6060

CMD ["/bin/bash"]
