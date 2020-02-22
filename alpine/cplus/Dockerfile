# C++ developement and debug base docker image.
#
# Using the image:
# - For gdb debugging, start docker with '--cap-add=SYS_PTRACE --security-opt seccomp=unconfined'.
# - For exposing all ports, add '--network="host'.
#

FROM alpine:3.11

# Build tools
RUN apk --no-cache add g++ linux-headers

# Debug tools
RUN apk --no-cache add gdb strace

# Convinience packages
RUN apk --no-cache add bash nano

CMD ["/bin/bash"]
