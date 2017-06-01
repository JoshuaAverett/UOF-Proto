# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

include_directories(${boost_include_dir})

set(client_source_files
	main.c
	)

set(client_header_files
	main.h
	)

add_subdirectory(system)

set_source_files_properties(${client_header_files} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND client_source_files ${client_header_files})

add_executable(client ${client_source_files})
target_link_libraries(client library)
