cmake_minimum_required(VERSION 3.6)
project(EDMW-Modding-Tools)
find_package(XP-CMake REQUIRED) #we need advanced cmake modules

set(CMAKE_CXX_STANDARD 17)

XPC_AutoBuildType()
XPC_OptForHost()
XPC_SetCompileDefinitions()

find_package(StdPlusPlus REQUIRED)

add_subdirectory(src_db_editor)
add_subdirectory(src_ssaEdit)

add_executable(DBEditor ${SOURCE_FILES_DBEDITOR})
target_link_libraries(DBEditor Std++ Std++Static)

#add_executable(ssaEdit ${SOURCE_FILES_SSAEDIT})
#target_link_libraries(ssaEdit ${LIBS})
