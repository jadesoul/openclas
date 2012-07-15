cmake_minimum_required(VERSION 2.6)
project(unit_test)
# add_definitions("-g")
find_package(Boost REQUIRED)
include_directories(../include)
link_libraries(-lboost_iostreams -lboost_zlib) 
add_executable(unit_test unit_test.cpp)
add_custom_command(
	TARGET unit_test
	POST_BUILD
	COMMAND cp unit_test ${CMAKE_SOURCE_DIR}/bin
	COMMENT "Postbuild Action"
)