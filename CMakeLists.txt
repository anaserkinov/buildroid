cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)

project(Buildroid)

find_package(cpprestsdk REQUIRED)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

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

add_subdirectory("sqlite_cpp")
add_subdirectory("tgbot_fragment")

add_subdirectory(libgit2)


include_directories(
    "sqlite_cpp/include"
    "tgbot_fragment/tgbot-cpp/include/tgbot"
    "tgbot_fragment/include"
    "src/include"
    "libgit2/include"
)

target_link_libraries(Buildroid PRIVATE
tgbot_fragment
sqlite_cpp
TgBot
cpprestsdk::cpprest
libgit2package
)