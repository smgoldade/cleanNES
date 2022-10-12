cmake_minimum_required(VERSION 3.22)
project(cleanNES)

set(CMAKE_CXX_STANDARD 23)
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(FATAL_ERROR "The only supported compiler for the project is MSVC")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /fp:fast)
    if(CMAKE_BUILD_TYPE EQUAL Release)
        add_compile_options(/O2)
    endif()
    if(CMAKE_BUILD_TYPE EQUAL Debug)
        add_compile_options(/fsanitize=address)
    endif()
endif ()

##########################################
# Third Party Dependencies
#
##########################################
#add_subdirectory(third-party/glfw EXCLUDE_FROM_ALL)
#add_subdirectory(third-party/glm EXCLUDE_FROM_ALL)
add_subdirectory(third-party/glad EXCLUDE_FROM_ALL)


##########################################
# Fetched Libraries:
# - googletest (gtest)
# - spdlog
# - glfw
# - glm
##########################################
include(FetchContent)
FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(gtest)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(spdlog)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
)
FetchContent_MakeAvailable(glm)


add_executable(cleanNES WIN32)
target_sources(cleanNES PRIVATE src/main.cpp)
target_link_libraries(cleanNES PRIVATE glad glfw glm spdlog::spdlog)