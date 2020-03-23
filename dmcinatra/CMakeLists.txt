cmake_minimum_required(VERSION 3.2)

PROJECT(dmcinatra)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMCINATRA_VERSION_MAJOR "1")
SET(DMCINATRA_VERSION_MINOR "0")
SET(DMCINATRA_VERSION_PATCH "1")
SET(DMCINATRA_VERSION "${DMCINATRA_VERSION_MAJOR}.${DMCINATRA_VERSION_MINOR}.${DMCINATRA_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMCINATRA_VERSION}")

OPTION(USE_DMCINATRA "use dmcinatra" OFF)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/dmcinatra_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dmcinatra_config.h)

ADD_DEFINITIONS(-DUSE_DMASIO)
ADD_DEFINITIONS(-DASIO_STANDALONE)
ADD_DEFINITIONS(-DGFLAGS_DLL_DECL=)

ModuleInclude("asio" "thirdparty/asio")
ModuleInclude("cinatra" "thirdparty/cinatra")
ModuleImport("dmsys" "thirdparty/dmsys")

LibImport("dmcinatra" "src/dmcinatra_module")
ExeImport("test" "dmcinatra;dmsys")

#ADD_CUSTOM_COMMAND(
#TARGET dmcinatratest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmcinatratest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmcinatra
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMCINATRA_LIBS "dmcinatra")
#MARK_AS_ADVANCED(${DMCINATRA_LIBS})