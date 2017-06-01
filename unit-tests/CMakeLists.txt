# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

include_directories(${boost_include_dir})

set(unit_test_source_files
	main.c
	test.c
	)

set(unit_test_header_files
	main.h
	test.h

	allocator-test.h
	compiler-test.h
	sockets-test.h
	symmetric-test.h
	threads-test.h
	vector-test.h
	)

set_source_files_properties(${unit_test_header_files} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND unit_test_source_files ${unit_test_header_files})

add_executable(unit-tests ${unit_test_source_files})
target_link_libraries(unit-tests library)
