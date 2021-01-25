cmake_minimum_required(VERSION 3.17)
project(String_)

set(CMAKE_CXX_STANDARD 17)

find_package(gtest REQUIRED)
find_package(Threads REQUIRED)
enable_testing()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}  ${GTEST_INCLUDE_DIRS})

add_executable(Test main_test.cpp)
add_test(Test ${PROJECT_SOURCE_DIR}/bin/testing)
#add_executable(main main.cpp)


add_library(myString SHARED myString.cpp myString.h)

#target_link_libraries(main myString)
target_link_libraries(Test myString)
target_link_libraries(Test Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
