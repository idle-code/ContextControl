enable_testing()

include_directories(../src)

#find_package(GTest REQUIRED "../extern/gtest")
set(GTEST_INCLUDE_DIR "../extern/gtest/include")
include_directories(${GTEST_INCLUDE_DIR})

file(GLOB TestSources *.cpp)

set(TestLibs ContextControlTree gtest_main)

add_executable(Tests ${TestSources})
target_link_libraries(Tests ${TestLibs})
add_test(Tests Tests)

