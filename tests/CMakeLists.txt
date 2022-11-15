set(CMAKE_CXX_STANDARD 23)
if (NOT MSVC)
    message(FATAL_ERROR "The only supported compiler for the project is MSVC")
endif()

if (MSVC)
    add_compile_options(/W4 /fp:fast /experimental:module)
    if(CMAKE_BUILD_TYPE EQUAL Release)
        add_compile_options(/O2)
    endif()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
        add_compile_options(/fsanitize=address)
    endif()
endif ()

#########################################
# cleanNES Test Executable Target Setup
#########################################
enable_testing()
add_executable(cleanNESTest vector_test.cpp)
target_link_libraries(cleanNESTest PRIVATE gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(cleanNESTest)

add_test(cleanNESTest COMMAND cleanNESTest)

