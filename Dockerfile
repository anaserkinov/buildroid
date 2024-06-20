FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR buildroid

COPY config.txt .
COPY tools.sh .
RUN chmod +x tools.sh

RUN /bin/bash -c './tools.sh --install_deps'

COPY shared shared
RUN /bin/bash -c './tools.sh --buildLibs'

COPY libs libs
COPY src src
COPY CMakeLists.txt .
COPY config.txt .
RUN /bin/bash -c './tools.sh --build'

RUN rm -rf shared
RUN rm -rf libs src CMakeLists.txt config.t