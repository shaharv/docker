FROM alpine:3.8

ENV LANG C.UTF-8

# Install useful packages
RUN apk --no-cache add \
	bash file nano

# Install build tools
RUN apk --no-cache add \
	binutils cmake coreutils g++ git make

# Install OpenJDK 8
RUN apk --no-cache add openjdk8
