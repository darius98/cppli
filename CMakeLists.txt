cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

list(APPEND cppli_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/argument.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/flag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numeric_argument.cpp
)

add_library(cppli_obj OBJECT ${cppli_src})
target_include_directories(cppli_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(cppli $<TARGET_OBJECTS:cppli_obj>)
target_include_directories(cppli_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS cppli ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION .)

if (NOT TARGET kktest)
    find_library(kktest kktest /usr/local/lib/)
endif()

if (TARGET kktest)
    # We have access to the kktest CMAKE scripts.
    add_kktest(cppli_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/choice_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/parser_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/flag_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/numeric_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/help_test.cpp
    )
elseif (kktest)
    add_executable(cppli_test
        ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/choice_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/parser_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/flag_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/numeric_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/help_test.cpp
    )
    target_link_libraries(cppli_test kktest)
else()
    message(WARNING "Cannot build test: kktest library not installed.")
endif()
