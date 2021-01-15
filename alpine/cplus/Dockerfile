# C++ developement and debug base docker image.
#
# Using the image:
# - For gdb debugging: "docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -it <image name>".
# - For exposing all ports, add '--network="host'.
#

FROM alpine:3.13

# Build tools
RUN apk --no-cache add cmake g++ linux-headers make

# Debug tools
RUN apk --no-cache add gdb strace py3-pip

# Convinience packages
RUN apk --no-cache add bash nano

# Upgrade pip
RUN pip3 install --upgrade pip

CMD ["/bin/bash"]
