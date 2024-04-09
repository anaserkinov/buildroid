cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)

project(Buildroid)

find_package(cpprestsdk REQUIRED)

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
cpprestsdk::cpprest
libgit2package
)