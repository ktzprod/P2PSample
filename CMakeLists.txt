cmake_minimum_required(VERSION 3.10)

project(peer-sample
    VERSION
    1.0.0
    DESCRIPTION
    "Sample app for light P2P message service"
    LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sources src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE -lpthread)

# Build tests
add_subdirectory(tests)
