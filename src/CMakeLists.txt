cmake_minimum_required(VERSION 2.6)
project(openclas)

# add_definitions("-g")

find_package(Boost REQUIRED)
include_directories(../include)
link_libraries(-lboost_iostreams -lboost_zlib)

add_executable(openclas_seg openclas_seg.cpp)
add_custom_command(
	TARGET openclas_seg
	POST_BUILD
	COMMAND cp openclas_seg ${CMAKE_SOURCE_DIR}/bin
	COMMENT "Postbuild Action: move openclas_seg to bin"
)

add_executable(openclas_segtag openclas_segtag.cpp)
add_custom_command(
	TARGET openclas_segtag
	POST_BUILD
	COMMAND cp openclas_segtag ${CMAKE_SOURCE_DIR}/bin
	COMMENT "Postbuild Action: move openclas_segtag to bin"
)

add_executable(openclas_test openclas_test.cpp)
add_custom_command(
	TARGET openclas_test
	POST_BUILD
	COMMAND cp openclas_test ${CMAKE_SOURCE_DIR}/bin
	COMMENT "Postbuild Action: move openclas_test to bin"
)
