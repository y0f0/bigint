cmake_minimum_required(VERSION 3.14)
project(LN_with_tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        MyString.cpp
        main.cpp
        LN.cpp
        util.cpp
        solve.h MyString.cpp)

set(HEADER_FILES
        MyString.h
        return_codes.h
        LN.h
        util.h
        )

add_executable(BigInteger_run ${SOURCE_FILES})

add_subdirectory(Google_tests)

