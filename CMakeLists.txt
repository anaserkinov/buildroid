cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)

project(Buildroid)

set(JSON_INC_PATH external/vcpkg/packages/jsoncpp_x64-linux/include)
set(JSON_LIB_PATH external/vcpkg/packages/jsoncpp_x64-linux/lib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)


file(
    GLOB 
    SOURCE_FILES 
    ${SOURCE_DIR}/*.cpp
    ${SOURCE_DIR}/fragments/*.cpp
    ${SOURCE_DIR}/tgbot_fragment_db_impl/*.cpp
    )

add_executable(
    Buildroid 
    ${SOURCE_FILES}
    )

add_subdirectory(${LIBS_DIR}/sqlite_cpp)
add_subdirectory(${LIBS_DIR}/tgbot_fragment)
add_subdirectory(${LIBS_DIR}/libgit2)


target_include_directories(Buildroid PRIVATE ${JSON_INC_PATH})
target_link_directories(Buildroid PRIVATE ${JSON_LIB_PATH})

include_directories(
    "libs/sqlite_cpp/include"
    "libs/tgbot_fragment/tgbot-cpp/include/tgbot"
    "libs/tgbot_fragment/include"
    "src/include"
    "libs/libgit2/include"
)

target_link_libraries(Buildroid PRIVATE
tgbot_fragment
sqlite_cpp
TgBot
libgit2package
jsoncpp)