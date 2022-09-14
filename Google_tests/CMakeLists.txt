project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        tests_from_problem_text ../util.cpp ../LN.cpp ../MyString.cpp
        all_tests.cpp
        tests_from_problem_text/tests_from_problem_text.h
        tests_multiplication/tests_multiplitcation.h
        tests_addition/tests_addition.h
        tests_subtraction/tests_subtraction.h
)

target_link_libraries(tests_from_problem_text  gtest gtest_main)
