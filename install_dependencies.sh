cd external

#install jsoncpp
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/Microsoft/vcpkg.git vcpkg
fi
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install jsoncpp
