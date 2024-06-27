FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR buildroid

COPY config.txt .
COPY tools.sh .
RUN chmod +x tools.sh

ENV ANDROID_SDK_URL https://dl.google.com/android/repository/commandlinetools-linux-11076708_latest.zip
ENV ANDROID_HOME /usr/local/android-sdk-linux
ENV ANDROID_BUILD_TOOLS_VERSION 34.0.0
ENV ANDROID_VERSION 34

ENV JAVA_URL_PATH jbrsdk-17.0.10-linux-x64-b1087.21
ENV JAVA_HOME /usr/local/java
ENV JAVA_URL https://cache-redirector.jetbrains.com/intellij-jbr/$JAVA_URL_PATH.tar.gz

ENV PATH ${ANDROID_HOME}/build-tools/${ANDROID_BUILD_TOOLS_VERSION}:${JAVA_HOME}/bin:$PATH

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