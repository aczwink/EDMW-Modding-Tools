cmake_minimum_required(VERSION 3.6)
project(EDMW-Modding-Tools)

set(CMAKE_CXX_STANDARD 11)

#debug or release
if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions(-D_DEBUG)
else()
    message(FATAL_ERROR "Unknown build type. Must be either 'Debug' or 'Release'")
endif()

find_library(ACSTDLIB_LIBRARY NAMES ACStdLib_d)
find_library(ACSTDLIBSTATIC_LIBRARY NAMES ACStdLibStatic_d)

set(LIBS ${ACSTDLIB_LIBRARY} ${ACSTDLIBSTATIC_LIBRARY})

add_subdirectory(src_db_editor)
add_subdirectory(src_ssaEdit)

add_executable(DBEditor ${SOURCE_FILES_DBEDITOR})
target_link_libraries(DBEditor ${LIBS})

add_executable(ssaEdit ${SOURCE_FILES_SSAEDIT})
target_link_libraries(ssaEdit ${LIBS})
