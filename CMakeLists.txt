cmake_minimum_required(VERSION 3.2)

PROJECT(dmcinatra)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

SET(DMCINATRA_VERSION_MAJOR "1")
SET(DMCINATRA_VERSION_MINOR "0")
SET(DMCINATRA_VERSION_PATCH "1")
SET(DMCINATRA_VERSION "${DMCINATRA_VERSION_MAJOR}.${DMCINATRA_VERSION_MINOR}.${DMCINATRA_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMCINATRA_VERSION}")

OPTION(USE_DMCINATRA "use dmcinatra" OFF)

SET(ENABLE_GZIP OFF)
SET(ENABLE_SSL ON)
SET(ENABLE_CLIENT_SSL ON)
SET(ENABLE_ASIO_STANDALONE ON)

if (ENABLE_SSL)
	add_definitions(-DCINATRA_ENABLE_SSL)
	message(STATUS "Use SSL")
endif()

if(ENABLE_CLIENT_SSL)
	add_definitions(-DCINATRA_ENABLE_CLIENT_SSL)
endif()

ADD_DEFINITIONS(-DUSE_DMASIO)
ADD_DEFINITIONS(-DASIO_STANDALONE)
ADD_DEFINITIONS(-DGFLAGS_DLL_DECL=)

ModuleInclude("asio" "thirdparty/asio")
ModuleInclude("cinatra" "thirdparty/cinatra")

ModuleImport("dmopenssl" "thirdparty/dmopenssl")

IF(WIN32)
    ExeImport("test" "crypto;ssl")
ELSE(UNIX)
    find_library(LIB_STD_FS stdc++fs)
    IF(LIB_STD_FS_FOUND)
        ExeImport("test" ${LIB_STD_FS_LIBRARIES};crypto;ssl)
    ELSE(LIB_STD_FS_FOUND)
        ExeImport("test" "stdc++fs;crypto;ssl")
    ENDIF(LIB_STD_FS_FOUND)
ENDIF(WIN32)
