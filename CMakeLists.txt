cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SDLTest VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE LIB_FILES lib/*.lib)
add_executable(SDLTest ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(SDLTest PUBLIC include)
target_link_libraries(SDLTest PUBLIC ${LIB_FILES})