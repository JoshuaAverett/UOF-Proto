# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

include_directories(${boost_include_dir})

set(library_source_files
	allocator.c
	compress.c
	deserializer.c
	error.c
	event.c
	serializer.c
	stream.c
	task.c
	)

set(library_header_files
	allocator.h
	compress.h
	error.h
	event.h
	master.h
	serializer.h
	stream.h
	task.h
	type-info.h
	)

add_subdirectory(allocators)
add_subdirectory(collections)
add_subdirectory(crypto)
add_subdirectory(facilities)
add_subdirectory(network)
add_subdirectory(system)

list(APPEND library_source_files ${library_header_files})

set_source_files_properties(${library_header_files} PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(library STATIC ${library_source_files})

find_package(Threads)
target_link_libraries(library ${CMAKE_THREAD_LIBS_INIT})

if(UNIX AND NOT APPLE)
    target_link_libraries(library rt)
endif()
