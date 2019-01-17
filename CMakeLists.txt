cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_library(cppli
        src/argument_impl.cpp
        src/cppli_impl.cpp
        src/cppli_interface.cpp)
target_include_directories(cppli PUBLIC include)


find_library(kktest kktest /usr/local/lib/)
message(${kktest})

add_executable(cppli_test test/cppli_test.cpp)
target_link_libraries(cppli_test PUBLIC cppli kktest)
