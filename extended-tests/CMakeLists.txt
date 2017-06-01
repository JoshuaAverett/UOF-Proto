# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

include_directories(${boost_include_dir})

set(extended_test_source_files
	main.c
	test.c
	)

set(extended_test_header_files
	main.h
	test.h

	hash_table-test.h
	)

set_source_files_properties(${extended_test_header_files} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND extended_test_source_files ${extended_test_header_files})

add_executable(extended-tests ${extended_test_source_files})
target_link_libraries(extended-tests library)
