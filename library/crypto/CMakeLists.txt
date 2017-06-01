# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/asymmetric.c
	${CMAKE_CURRENT_SOURCE_DIR}/symmetric.c
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/asymmetric.h
	${CMAKE_CURRENT_SOURCE_DIR}/symmetric.h
	)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
