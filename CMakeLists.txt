cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_INSTALL_PREFIX /usr/local/)

add_library(cppli_objects OBJECT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cppli.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/argument.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/flag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/numeric_argument.cpp
)
target_include_directories(cppli_objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(cppli $<TARGET_OBJECTS:cppli_objects>)
target_link_libraries(cppli PUBLIC cppli_objects)
install(TARGETS cppli ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION .)

if (NOT TARGET kktest)
    find_library(kktest kktest /usr/local/lib/)
endif()

if (TARGET kktest OR kktest)
    add_executable(cppli_test EXCLUDE_FROM_ALL
        ${CMAKE_CURRENT_SOURCE_DIR}/test/choice_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/cppli_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/flag_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/numeric_argument_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test/help_test.cpp
    )
    target_link_libraries(cppli_test PRIVATE kktest cppli)
    target_include_directories(cppli_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
    message(WARNING "Cannot build test: kktest library not installed.")
endif()
