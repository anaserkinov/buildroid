if [ $1 == "--install_deps" ]; then
apt-get update
apt install -y openssl libssl-dev libboost-all-dev libcpprest-dev unzip zip git curl
apt install -y gcc clang pkg-config cmake make gdb


mkdir -p $ANDROID_HOME /usr/local


if [ ! -d "external/vcpkg" ]; then
git clone https://github.com/Microsoft/vcpkg.git external/vcpkg
fi 

cd external/vcpkg && \
./bootstrap-vcpkg.sh && \
./vcpkg integrate install && \
./vcpkg install jsoncpp && \
cd  ../..

curl -L -o /usr/local/jbr.tar.gz $JAVA_URL
cd /usr/local && \
tar zxf jbr.tar.gz && \
rm jbr.tar.gz && \
mv $JAVA_URL_PATH java && \

curl -o $ANDROID_HOME/android-sdk.zip $ANDROID_SDK_URL
cd $ANDROID_HOME && \
unzip android-sdk.zip && \
rm android-sdk.zip && \

yes | ${ANDROID_HOME}/cmdline-tools/bin/sdkmanager --sdk_root=$ANDROID_HOME --licenses
$ANDROID_HOME/cmdline-tools/bin/sdkmanager --sdk_root=$ANDROID_HOME --update
$ANDROID_HOME/cmdline-tools/bin/sdkmanager --sdk_root=$ANDROID_HOME "build-tools;${ANDROID_BUILD_TOOLS_VERSION}" \
    "build-tools;${ANDROID_BUILD_TOOLS_VERSION}" \
    "platforms;android-${ANDROID_VERSION}" \
    "platform-tools"

elif [ $1 == "--buildLibs" ]; then
mkdir -p deps && \
rm -rf deps/* && \
mkdir -p shared/build && \
rm -rf shared/build/* && \

cd shared/build && \
cmake .. && \
make && \
cd ../../ && \
mv shared/build/libBuildroid_Libs.so deps && \

cd shared/libgit2 && \
mkdir -p build && \
rm -rf build/* && \
cd build && \
cmake .. && \
make && \
cd ../../.. && \
mv shared/libgit2/build/libgit2.so.1.8.2 deps && \
mv shared/libgit2/build/libgit2.so.1.8 deps && \
mv shared/libgit2/build/libgit2.so deps

elif [ $1 == "--build" ]; then
mkdir -p build && \
rm -rf build/* && \
cd build && \
cmake .. && \
make
fi