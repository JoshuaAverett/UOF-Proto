# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/circuit.c
	${CMAKE_CURRENT_SOURCE_DIR}/ip-address.c
	${CMAKE_CURRENT_SOURCE_DIR}/packet.c
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/circuit.h
	${CMAKE_CURRENT_SOURCE_DIR}/ip-address.h
	${CMAKE_CURRENT_SOURCE_DIR}/packet.h
	)

add_subdirectory(packets)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)

