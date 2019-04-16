# For gdb, start docker with "--cap-add=SYS_PTRACE --security-opt seccomp=unconfined".

FROM alpine:3.8

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash coreutils file nano unzip

# Install OpenJDK packages
RUN set -ex && \
	VER=8.181.13-r0 && \
	REPO=http://dl-cdn.alpinelinux.org/alpine/v3.5/community && \
	apk --no-cache add \
		openjdk8=$VER openjdk8-jre-base=$VER openjdk8-jre-lib=$VER openjdk8-jre=$VER openjdk8-dbg=$VER --repository=$REPO

# Install patched gdb for OpenJDK debugging
RUN set -ex && \
	apk add --no-cache python2 && \
	mkdir -p /temp && cd /temp && \
	wget https://github.com/shaharv/alpine-gdb-builds/releases/download/v0.1/gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	unzip gdb-8.3.50.20190410-git_x86-64_musl.zip && \
	cd gdb-8.3.50.20190410-git_x86-64_musl && \
	cp -a bin share /usr/local && \
	rm -rf /temp

CMD ["/bin/bash"]
