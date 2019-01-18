cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_INSTALL_PREFIX /usr/local/)

add_library(cppli
        src/argument.cpp
        src/argument_impl.cpp
        src/cppli_impl.cpp
        src/cppli_interface.cpp
        src/flag.cpp
        src/int_argument.cpp)
target_include_directories(cppli PUBLIC include)
install(TARGETS cppli ARCHIVE DESTINATION lib)
install(DIRECTORY include DESTINATION .)

find_library(kktest kktest /usr/local/lib/)

if (kktest)
    add_executable(cppli_test EXCLUDE_FROM_ALL test/cppli_test.cpp)
    target_link_libraries(cppli_test PUBLIC cppli kktest)
else()
    message("Cannot build test: kktest library not installed.")
endif()
