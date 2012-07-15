cmake_minimum_required(VERSION 2.6)
project(pyopenclas)

# add_definitions("-g")
add_definitions("-DBOOST_PYTHON_STATIC_LIB")

find_package(Boost REQUIRED)

include_directories(../include ../src /usr/include/python2.7)
link_directories(/usr/lib /usr/local/lib)
link_libraries(-lboost_iostreams -lboost_zlib -lboost_python -lpython2.7)

ADD_LIBRARY(pyopenclas SHARED pyopenclas.cpp)
add_custom_command(
	TARGET pyopenclas
	POST_BUILD
	COMMAND cp libpyopenclas.so ${CMAKE_SOURCE_DIR}/bin
	COMMENT "Postbuild Action: move pyopenclas to bin"
)

