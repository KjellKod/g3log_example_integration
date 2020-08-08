cmake_minimum_required (VERSION 3.12)
project(example_project)

find_package(g3log CONFIG REQUIRED)
message(
"g3log package:
    found: ${G3LOG_FOUND}
    include dir: ${G3LOG_INCLUDE_DIRS}
    libraries: ${G3LOG_LIBRARIES}"
)

include_directories(${G3LOG_INCLUDE_DIRS})
add_executable(example example_main.cpp)
target_link_libraries(example PUBLIC ${G3LOG_LIBRARIES})
