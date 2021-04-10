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

ADD_DEFINITIONS(-DUSE_DMASIO)
ADD_DEFINITIONS(-DASIO_STANDALONE)
ADD_DEFINITIONS(-DGFLAGS_DLL_DECL=)

ModuleInclude("asio" "thirdparty/asio")
ModuleInclude("cinatra" "thirdparty/cinatra")

IF(WIN32)
    ExeImport("test" "")
ELSE(UNIX)
    find_library(LIB_STD_FS stdc++fs)
    IF(LIB_STD_FS_FOUND)
        ExeImport("test" ${LIB_STD_FS_LIBRARIES})
    ELSE(LIB_STD_FS_FOUND)
        ExeImport("test" "stdc++fs")
    ENDIF(LIB_STD_FS_FOUND)
ENDIF(WIN32)
