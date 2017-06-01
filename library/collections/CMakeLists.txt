# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/atomic-bit-vector.h
	${CMAKE_CURRENT_SOURCE_DIR}/hash-table.h
	${CMAKE_CURRENT_SOURCE_DIR}/vector.h
	)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
