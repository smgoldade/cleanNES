cmake_minimum_required(VERSION 3.22)
project(cleanNES)

##########################################
# cleanNES Main Project
##########################################
add_subdirectory(src)

##########################################
# cleanNES Tests
##########################################
add_subdirectory(tests)

##########################################
# Fetched Libraries:
# - googletest (gtest)
# - spdlog
##########################################
include(FetchContent)
FetchContent_Declare(
        gtest
        SYSTEM
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_Declare(
        spdlog
        SYSTEM
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(gtest spdlog)