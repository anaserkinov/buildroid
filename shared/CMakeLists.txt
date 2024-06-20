cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(JSON_INC_PATH ../external/vcpkg/packages/jsoncpp_x64-linux/include)
set(JSON_LIB_PATH ../external/vcpkg/packages/jsoncpp_x64-linux/lib)

project(Buildroid_Libs)

add_subdirectory(${CMAKE_SOURCE_DIR}/sqlite_cpp sqlite_cpp)

add_library(Buildroid_Libs SHARED dummy.cpp)


target_include_directories(Buildroid_Libs PUBLIC 
    ${JSON_INC_PATH}
    "sqlite_cpp/include"
)
target_link_directories(Buildroid_Libs PUBLIC ${JSON_LIB_PATH})


set_property(TARGET Buildroid_Libs PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(sqlite_cpp PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(sqlite_cpp PROPERTIES POSITION_INDEPENDENT_CODE ON)


target_link_libraries(
    Buildroid_Libs PRIVATE
    sqlite_cpp
    jsoncpp
)