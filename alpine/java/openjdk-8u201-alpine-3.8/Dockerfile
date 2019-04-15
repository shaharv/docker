FROM alpine:3.8

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash coreutils file nano

# Install OpenJDK packages
RUN apk --no-cache add \
	openjdk8=8.201.08-r0 openjdk8-dbg=8.201.08-r0
