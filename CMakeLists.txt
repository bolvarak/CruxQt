#######################################################################################################################
### CMake Requirements ################################################################################################
#######################################################################################################################

## CMake Minimum Version
cmake_minimum_required(VERSION 3.7)

## Define the C++ version
set(CMAKE_CXX_STANDARD 11)

## Automoc
set(CMAKE_AUTOMOC ON)

## Project Name
project(Crux)

## Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Sql)

#######################################################################################################################
### Crux Shared Library Qt Definitions ################################################################################
#######################################################################################################################

## Define our source files
set(CRUXLIB_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/Core/Is.hpp
	${PROJECT_SOURCE_DIR}/Core/Config.hpp
	${PROJECT_SOURCE_DIR}/Core/Request.hpp
	${PROJECT_SOURCE_DIR}/Core/Container/Cookie.hpp
	${PROJECT_SOURCE_DIR}/Provider/Sql/Driver.hpp
	${PROJECT_SOURCE_DIR}/Provider/Sql/Engine.hpp
		${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/Lite.hpp
		${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/My.hpp
		${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/Pg.hpp
#			${PROJECT_SOURCE_DIR}/Fluent/Sql/Collection.hpp
			${PROJECT_SOURCE_DIR}/Fluent/Sql/Model.hpp
	${PROJECT_SOURCE_DIR}/Grammar/Inflection.hpp
	${PROJECT_SOURCE_DIR}/Crypto/OpenSSL.hpp

	${PROJECT_SOURCE_DIR}/Core/Config.cpp
	${PROJECT_SOURCE_DIR}/Core/Request.cpp
	${PROJECT_SOURCE_DIR}/Core/Container/Cookie.cpp
	${PROJECT_SOURCE_DIR}/Provider/Sql/Driver.cpp
		${PROJECT_SOURCE_DIR}/Provider/Sql/Engine.cpp
			${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/Lite.cpp
			${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/My.cpp
			${PROJECT_SOURCE_DIR}/Provider/Sql/Dialect/Pg.cpp
#				${PROJECT_SOURCE_DIR}/Fluent/Sql/Collection.cpp
				${PROJECT_SOURCE_DIR}/Fluent/Sql/Model.cpp
	${PROJECT_SOURCE_DIR}/Grammar/Inflection.cpp
	${PROJECT_SOURCE_DIR}/Crypto/OpenSSL.cpp
)

#######################################################################################################################
### Crux Shared Library Definition ####################################################################################
#######################################################################################################################

## Define our library
add_library(QtCrux SHARED ${CRUXLIB_SOURCE_FILES})

## Link our external libraries
target_link_libraries(QtCrux Qt5::Core Qt5::Network Qt5::Sql)

#######################################################################################################################
### Test Application Definition #######################################################################################
#######################################################################################################################

## Define our executable
add_executable(app.bgi
		${PROJECT_SOURCE_DIR}/Example/main.cpp
#		${PROJECT_SOURCE_DIR}/Example/ExampleModel.hpp
#		${PROJECT_SOURCE_DIR}/Example/ExampleModel.cpp
)

## Link our library to the executable
target_link_libraries(app.bgi QtCrux)
