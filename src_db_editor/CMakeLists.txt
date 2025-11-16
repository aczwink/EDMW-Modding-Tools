set(SOURCE_FILES_DBEDITOR
	${SOURCE_FILES_DBEDITOR}

	#db
	${CMAKE_CURRENT_SOURCE_DIR}/db/DB.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/db/DB.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/db/DBField.hpp

	#ui
	${CMAKE_CURRENT_SOURCE_DIR}/ui/MainWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/MainWindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/ObjectEditorController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/ObjectEditorController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/ObjectNavigatorController.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/ObjectNavigatorController.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/ui/UIController.hpp

	#.
	${CMAKE_CURRENT_SOURCE_DIR}/definitions.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

	PARENT_SCOPE)