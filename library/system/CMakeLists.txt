# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/random.c
	${CMAKE_CURRENT_SOURCE_DIR}/sockets.c
	${CMAKE_CURRENT_SOURCE_DIR}/threads.c
	${CMAKE_CURRENT_SOURCE_DIR}/time.c
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/random.h
	${CMAKE_CURRENT_SOURCE_DIR}/sockets.h
	${CMAKE_CURRENT_SOURCE_DIR}/threads.h
	${CMAKE_CURRENT_SOURCE_DIR}/time.h
	)

add_subdirectory(macos)
add_subdirectory(linux)
add_subdirectory(windows)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
