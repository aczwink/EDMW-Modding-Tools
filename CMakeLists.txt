cmake_minimum_required(VERSION 3.6)
project(EDMW-Modding-Tools)
find_package(XP-CMake REQUIRED) #we need advanced cmake modules

set(CMAKE_CXX_STANDARD 20)

XPC_AutoBuildType()
XPC_OptForHost()
XPC_SetCompileDefinitions()

find_package(StdPlusPlus REQUIRED)

add_subdirectory(src_db_editor)
add_subdirectory(src_ssaEdit)

add_library(edmwlib STATIC include/EDMW_DBCollection.hpp include/EDMW_ObjectSchema.hpp include/EDMW_Database.hpp src_lib/EDMW_Database.cpp src_lib/EDMW_ObjectSchema.cpp include/EDMW_DBObject.hpp)
target_include_directories(edmwlib PRIVATE "include")
target_link_libraries(edmwlib LINK_PUBLIC Std++ Std++Static)

add_executable(DBEditor ${SOURCE_FILES_DBEDITOR})
target_link_libraries(DBEditor Std++ Std++Static)

add_executable(dbdump src_dbdump/main.cpp)
target_include_directories(dbdump PRIVATE "include")
target_link_libraries(dbdump LINK_PUBLIC Std++ Std++Static edmwlib)

#add_executable(ssaEdit ${SOURCE_FILES_SSAEDIT})
#target_link_libraries(ssaEdit ${LIBS})
