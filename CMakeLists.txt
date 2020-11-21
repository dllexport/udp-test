cmake_minimum_required(VERSION 3.17)
project(udp_test)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.74.0 COMPONENTS coroutine context system regex date_time thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable(udp_test main.cpp)
target_link_libraries(udp_test ${Boost_LIBRARIES})