FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN mkdir -p external && cd external

RUN apt-get update && \
apt install -y openssl libssl-dev libboost-all-dev libcpprest-dev unzip zip git curl screen && \
apt install -y gcc clang pkg-config cmake make

COPY . .

RUN cd external/vcpkg && \
./bootstrap-vcpkg.sh && \
./vcpkg integrate install && \
./vcpkg install jsoncpp 

RUN mkdir -p build && \
cmake .. && \
make