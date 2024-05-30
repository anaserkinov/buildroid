mkdir -p external && cd external

#install openssl
sudo apt-get install openssl libssl-dev -y

#install boost
sudo apt-get install libboost-all-dev -y

#install cpprest
sudo apt-get install libcpprest-dev -y

#install jsoncpp
if [ ! -d "vcpkg" ]; then
    git clone https://github.com/Microsoft/vcpkg.git vcpkg
fi
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install jsoncpp
