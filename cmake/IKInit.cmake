cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

message(STATUS "import IKInit.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/IKConfig.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/IKPackage.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/IKBuild.cmake")
set(IKCMAKE_VERSION 0.1.0)

macro(IK_InitProject PROJECT_NAME_STR)
set(PROJECT_NAME ${PROJECT_NAME_STR})
IK_InitConfig()
# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 添加c++11标准支持
set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") # 可执行文件输出目录

if(NOT IK_RootProjectPath)
    set(IK_RootProjectPath ${PROJECT_SOURCE_DIR})
endif()

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


endmacro(IK_InitProject PROJECT_NAME_STR)


