cmake_minimum_required (VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(example_g3sinks)


get_directory_property(_vars_before VARIABLES)
find_package(g3log CONFIG REQUIRED)
get_directory_property(_vars VARIABLES)
list(REMOVE_ITEM _vars _vars_before ${_vars_before})
foreach(_var IN LISTS _vars)
    message(STATUS "${_var} = ${${_var}}")
endforeach()


message(
"g3log package:
    found: ${G3LOG_FOUND}
    include dir: ${G3LOG_INCLUDE_DIRS}
    libraries: ${G3LOG_LIBRARIES}"
)


get_directory_property(_vars2_before VARIABLES)
find_package(g3sinks CONFIG REQUIRED)
get_directory_property(_vars2 VARIABLES)
list(REMOVE_ITEM _vars2 _vars2_before ${_vars2_before})
foreach(_var IN LISTS _vars2)
    message(STATUS "${_var} = ${${_var}}")
endforeach()

message(
  "g3sinks:
     found: ${G3SINKS_FOUND}
     include dir: ${G3SINKS_INCLUDE_DIRS}
     libraries: ${G3SINKS_LIBRARIES}"
)


message(
  "g3sinks:
     found: ${g3sinks_FOUND}
     include dir: ${g3sinks_INCLUDE_DIRS}
     libraries: ${g3sinks_LIBRARIES}"
)


include_directories(${G3LOG_INCLUDE_DIRS})
include_directories(${G3SINKS_INCLUDE_DIRS})

add_executable(example_g3sinks example_g3sinks_main.cpp)
target_link_libraries(example_g3sinks PUBLIC ${G3LOG_LIBRARIES} ${G3SINKS_LIBRARIES})
