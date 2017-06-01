# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/basic-types.c
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/atomic-types.h
	${CMAKE_CURRENT_SOURCE_DIR}/basic-types.h
	${CMAKE_CURRENT_SOURCE_DIR}/compiler.h
	${CMAKE_CURRENT_SOURCE_DIR}/macros.h
	${CMAKE_CURRENT_SOURCE_DIR}/platform.h
	${CMAKE_CURRENT_SOURCE_DIR}/source-annotation.h
	${CMAKE_CURRENT_SOURCE_DIR}/utilities.h
	)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
