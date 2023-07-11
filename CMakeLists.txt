cmake_minimum_required(VERSION 3.10)

project(Buildroid)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(
    GLOB 
    SOURCE_FILES 
    ${SOURCE_DIR}/Main.cpp
    ${SOURCE_DIR}/DatabaseController.cpp
    ${SOURCE_DIR}/MainDatabase.cpp
    ${SOURCE_DIR}/fragments/*.cpp
    ${SOURCE_DIR}/tgbot_fragment_db_impl/*.cpp
    )

add_executable(
    Buildroid 
    ${SOURCE_FILES}
    )

add_subdirectory("sqlite_cpp")
add_subdirectory("tgbot_fragment")

include_directories(
    "sqlite_cpp/include"
    "tgbot_fragment/tgbot-cpp/include/tgbot"
    "tgbot_fragment/include"
    "src/include"
)

target_link_libraries(Buildroid 
tgbot_fragment
sqlite_cpp
TgBot
)