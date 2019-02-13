cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_INSTALL_PREFIX /usr/local/)

add_library(cppli
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/argument.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/flag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numeric_argument.cpp)
target_include_directories(cppli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS cppli ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION .)

if (NOT TARGET kktest)
    find_library(kktest kktest /usr/local/lib/)
endif()

if (TARGET kktest)
    # We have access to the kktest CMAKE scripts.
    add_kktest(cppli_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test/choice_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/parser_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/flag_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/numeric_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/help_test.cpp
    )
    target_link_libraries(cppli_test cppli)
elseif (kktest)
    add_executable(cppli_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test/choice_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/parser_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/flag_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/numeric_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/help_test.cpp
    )
    target_link_libraries(cppli_test kktest cppli)
else()
    message(WARNING "Cannot build test: kktest library not installed.")
endif()
