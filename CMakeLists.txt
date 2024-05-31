cmake_minimum_required(VERSION 3.14)

project(extend_py)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # don't use compiler-specific extensions

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(SRCS "hello_module.cpp" "hello_type.cpp")
add_library(HelloModule SHARED ${SRCS})

find_package(PythonLibs REQUIRED)

set_target_properties(
    HelloModule
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "HelloModule"
        LINKER_LANGUAGE CXX
        LINKER_LIBRARIES "${PYTHON_LIBRARIES}"
        INCLUDE_DIRECTORIES "/usr/include/python3.11;${PYTHON_INCLUDE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/tests"
)
