# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

list(APPEND client_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/main-apple.c
	${CMAKE_CURRENT_SOURCE_DIR}/main-linux.c
	${CMAKE_CURRENT_SOURCE_DIR}/main-windows.c
	)

list(APPEND client_header_files
	)

set(client_source_files ${client_source_files} PARENT_SCOPE)
set(client_header_files ${client_header_files} PARENT_SCOPE)
