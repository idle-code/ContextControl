find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
set(${Libs} "${Libs} ${Boost_LIBRARIES}")

include_directories(./)

file(GLOB ContextControlTreeSources Tree*.cpp)
file(GLOB ContextControlSources "ContextControl.cpp" "Expression.cpp")

#add_library(ContextControlTree ${ContextControlTreeSources})
add_library(ContextControl ${ContextControlSources} ${ContextControlTreeSources})
target_link_libraries(ContextControl ${Libs})

add_executable(ccsh "repl.cpp")
target_link_libraries(ccsh ${Libs})

