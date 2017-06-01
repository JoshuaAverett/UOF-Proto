# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND library_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/packet-create-circuit.c
	${CMAKE_CURRENT_SOURCE_DIR}/packet-circuit-created.c

	${CMAKE_CURRENT_SOURCE_DIR}/packet-create-stream.c
	${CMAKE_CURRENT_SOURCE_DIR}/packet-stream-created.c

	${CMAKE_CURRENT_SOURCE_DIR}/packet-test.c
	)

list(APPEND library_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/packet-list.h
	${CMAKE_CURRENT_SOURCE_DIR}/packet-header.h

	${CMAKE_CURRENT_SOURCE_DIR}/packet-create-circuit.h
	${CMAKE_CURRENT_SOURCE_DIR}/packet-circuit-created.h

	${CMAKE_CURRENT_SOURCE_DIR}/packet-create-stream.h
	${CMAKE_CURRENT_SOURCE_DIR}/packet-stream-created.h

	${CMAKE_CURRENT_SOURCE_DIR}/packet-test.h
	)

set(library_source_files ${library_source_files} PARENT_SCOPE)
set(library_header_files ${library_header_files} PARENT_SCOPE)
