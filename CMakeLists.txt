cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

project(Buildroid)

if(APPLE)
    message(STATUS "Configuring for macOS") 
    set(JSON_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/packages/jsoncpp_arm64-osx/include)
    set(JSON_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/packages/jsoncpp_arm64-osx/lib)  
elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux (Ubuntu or other distributions)")
    set(JSON_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/packages/jsoncpp_x64-linux/include)
    set(JSON_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/packages/jsoncpp_x64-linux/lib) 
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SHARED_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shared)

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

add_subdirectory(${LIBS_DIR}/tgbot_fragment)

target_include_directories(
    Buildroid PRIVATE
    ${JSON_INC_PATH}
    "shared/sqlite_cpp/include"
    "shared/libgit2/include"
    "libs/tgbot_fragment/tgbot-cpp/include/tgbot"
    "libs/tgbot_fragment/include"
    "src/include"
)

add_library(Buildroid_Libs SHARED IMPORTED)
add_library(libgit2 SHARED IMPORTED)



if(APPLE)
    set_target_properties(Buildroid_Libs PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/deps/libBuildroid_Libs.dylib
    )
    set_target_properties(libgit2 PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/deps/libgit2.dylib
    )  
elseif(UNIX AND NOT APPLE)
    set_target_properties(Buildroid_Libs PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/deps/libBuildroid_Libs.so
    )
    set_target_properties(libgit2 PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/deps/libgit2.so
    ) 
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

find_library(sqlite_cpp sqlite_cpp PATHS ${SHARED_LIBS_DIR}/build/sqlite_cpp)
find_library(jsoncpp jsoncpp PATHS ${JSON_LIB_PATH})

find_package(cpprestsdk REQUIRED)

target_link_libraries(Buildroid PRIVATE
Buildroid_Libs
libgit2
dl
tgbot_fragment
TgBot
cpprestsdk::cpprest
${sqlite_cpp}
${jsoncpp})