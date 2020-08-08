# g3log_example_integration
Example project of how to integrate with g3log

## Example of Building g3log, shared library,  in a local location
```
git clone https://github.com/KjellKod/g3log.git
cd g3log
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/home/kjell/opt ..
cmake --build . --target install
```

# Integrating the example with g3log
The content of the `CMakeLists.txt` is as follows:
```
cmake_minimum_required (VERSION 3.17)
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
```

## Building the example
```
cmake -DCMAKE_PREFIX_PATH=/home/kjell/opt ..
cmake --build .
```

## Running the example
In this case we installed g3log in a custom location
Since we built g3log this time as a shared libary the `LD_LIBRARY_PATH` must be set. 
```
LD_LIBRARY_PATH=/home/kjell/opt/lib/ ./example 
```



 
