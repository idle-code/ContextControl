find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
set(${Libs} "${Libs} ${Boost_LIBRARIES}")

include_directories(./)

file(GLOB ContextControlTreeSources Tree*.cpp)

add_library(ContextControlTree ${ContextControlTreeSources})
target_link_libraries(ContextControlTree ${Libs})

