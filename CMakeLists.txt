cmake_minimum_required(VERSION 3.22)

project(storm LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(TARGET test)

set(LIB_SRC
    storm/log.cc
    )

add_library(storm SHARED ${LIB_SRC})

# include_directories(${TARGET} storm)
add_executable(${TARGET}
    example/testStorm.cc
)
# add_dependencies(${TAEGET} storm)
target_link_libraries(${TARGET} storm)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)