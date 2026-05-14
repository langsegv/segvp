cmake_minimum_required(VERSION 3.16)

project(segvc-parser
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(SEGVC_PARSER_VERSION_METADATA "alpha.1")

option(IS_SHARED "Build shared library" ON)

if(IS_SHARED)
	add_library(segvc-parser SHARED)
else()
	add_library(segvc-parser STATIC)
endif()

file(GLOB_RECURSE SEGVC_PARSER_SOURCES
	CONFIGURE_DEPENDS
	src/*.c
	src/*.cpp
	src/*.cxx
)

target_sources(segvc-parser
	PRIVATE
		${SEGVC_PARSER_SOURCES}
)

target_include_directories(segvc-parser
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(segvc-parser PROPERTIES
		VERSION "${PROJECT_VERSION}-${SEGVC_PARSER_VERSION_METADATA}"
		SOVERSION 1
		OUTPUT_NAME "segvcparser"
)