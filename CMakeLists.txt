cmake_minimum_required(VERSION 3.11)

set(PROJECT_NAME "IKit")
set(PROJECT_VERSION 0.0.3)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(IKInit)
IK_InitProject(${PROJECT_NAME})

message(STATUS "[Project] ${PROJECT_NAME} ${PROJECT_VERSION}")

IK_AddSubDirsRec(src)
IK_AddSubDirsRec(include)

IK_Export(
  TARGET
  DIRECTORIES
    "include"
)
