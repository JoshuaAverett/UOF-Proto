# Copyright (C) 76 Enterprises LLC - All Rights Reserved
# See the file "license.txt" for the full copyright notice

set(third_party_downloads ${CMAKE_CURRENT_SOURCE_DIR}/downloads)
file(MAKE_DIRECTORY ${third_party_downloads})

function(add_third_party name version sha1)
	set(file_name "${name}-${version}.tgz")
	set(file_source "http://files.yaff.me/third-party/${file_name}")
	set(file_dest "${CMAKE_CURRENT_SOURCE_DIR}/downloads/${file_name}")
	set(final_dir ${CMAKE_CURRENT_SOURCE_DIR}/${name}-${version})
	
	
	set(do_download 0)
	if(NOT EXISTS ${file_dest})
		message(STATUS "${name} not found.")
		set(do_download 1)
	else()
		file(SHA1 ${file_dest} current_sha1)
		if(NOT ${sha1} STREQUAL ${current_sha1})
			message(STATUS "${name} invalid.\nExpected ${sha1}, got ${current_sha1}.")
			set(do_download 1)
		else()
			message(STATUS "${name} found and verified.")
		endif()
	endif()
	
	if(do_download EQUAL 1)
		message(STATUS "Downloading ${name} to ${file_dest}")
		file(DOWNLOAD ${file_source} ${file_dest} STATUS status SHOW_PROGRESS EXPECTED_HASH SHA1=${sha1})
		
		list(GET status 0 error_code)
		message(STATUS "Got status code ${error_code}")
		if(NOT error_code EQUAL 0)
			list(GET status 1 error_message)
			message(FATAL_ERROR "Failed to download ${name}. Error ${error_code}: ${error_message}")
		endif()
		
		file(MAKE_DIRECTORY ${final_dir})
		
		execute_process(
			COMMAND ${CMAKE_COMMAND} -E tar xzf ${file_dest}
			WORKING_DIRECTORY ${final_dir}
			)
	endif()
	
	add_subdirectory(${final_dir})
	string(TOLOWER ${name} name)
	message(STATUS "Created include dir for ${name}: ${${name}_include_dir}")
endfunction()

set(glew_version 1.10.0)
set(glew_sha1 2c65b30d8ad5727beaf96f08ba129015acdea147)
add_third_party("GLEW" ${glew_version} ${glew_sha1})

set(boost_version 1.55.0)
set(boost_sha1 bf0c06ce9f84a53a059dad223ad785be7e5f8436)
add_third_party("Boost" ${boost_version} ${boost_sha1})
