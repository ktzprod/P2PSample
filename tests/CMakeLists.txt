cmake_minimum_required(VERSION 3.10)

project(peer-sample-tests
    VERSION
    1.0.0
    DESCRIPTION
    "Launch unit tests for peer-sample code base"
    LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(source_files
    ../src/client.cpp
    ../src/peer_connection.cpp
    ../src/server.cpp
)

file(GLOB test_files *.cpp)

add_executable(${PROJECT_NAME} ${source_files} ${test_files})
target_include_directories(${PROJECT_NAME} PRIVATE ../src)
target_link_libraries(${PROJECT_NAME} PRIVATE -lpthread)
