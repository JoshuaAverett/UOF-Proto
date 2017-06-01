# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/random.c
	${CMAKE_CURRENT_SOURCE_DIR}/sockets.c
	${CMAKE_CURRENT_SOURCE_DIR}/threads.c
	${CMAKE_CURRENT_SOURCE_DIR}/time.c
	)

list(APPEND library_header_files
	)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
