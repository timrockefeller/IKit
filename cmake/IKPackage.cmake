function(IK_AddSubDirsRec path)
  message(STATUS "----------")
  file(GLOB_RECURSE children LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/${path}/*)
  set(dirs "")
  list(APPEND children "${CMAKE_CURRENT_SOURCE_DIR}/${path}")
  foreach(item ${children})
    if(IS_DIRECTORY ${item} AND EXISTS "${item}/CMakeLists.txt")
      list(APPEND dirs ${item})
    endif()
  endforeach()
  foreach(dir ${dirs})
    add_subdirectory(${dir})
  endforeach()
endfunction()

### IK_UnityArgs
## (tarLIST STR1 STR2 ...)
## -> tarLIST = "STR1 STR2 ..."
function(IK_UnityArgs)
    set(ARGLIST "")
    set(IK_INDEX 1)
    if(${ARGC} LESS 2)
        set(ARGLIST " ")
    else()
        while(IK_INDEX LESS ${ARGC})
            set(ARGLIST "${ARGLIST} ${ARGV${IK_INDEX}}")
            math(EXPR IK_INDEX "${IK_INDEX} + 1")  
        endwhile()
    endif()
    set(${ARGV0} ${ARGLIST} PARENT_SCOPE)
endfunction(IK_UnityArgs)

function(IK_GlobGroupSrcs)
	cmake_parse_arguments("ARG" "" "RST" "PATHS" ${ARGN})
	set(SOURCES "")
	foreach(path ${ARG_PATHS})
		file(GLOB_RECURSE pathSources
			"${path}/*.h"
			"${path}/*.hpp"
			"${path}/*.inl"
			"${path}/*.c"
			"${path}/*.cc"
			"${path}/*.cpp"
			"${path}/*.cxx"
		)
		list(APPEND SOURCES ${pathSources})
    endforeach()
    IK_UnityArgs(SOURCES ${SOURCES})
	set(${ARG_RST} ${SOURCES} PARENT_SCOPE)
endfunction()

### Setup Target
##  TODO setup target with less options, seperate by extensions
## 

function(IK_SetupTarget)

endfunction()

function(IK_AddPackage _name version)
# 添加第三方依赖包
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(add_FetchContent_MakeAvailable.cmake)
endif()
message(STATUS "importing ${_name}")
set(IKIT_GIT_TAG  ${version})  # 指定版本
set(IKIT_GIT_URL  "https://github.com/timrockefeller/${_name}.git")  # 指定git仓库地址
FetchContent_Declare(
  ${_name}
  GIT_REPOSITORY    ${IKIT_GIT_URL}
  GIT_TAG           ${IKIT_GIT_TAG}
)
FetchContent_MakeAvailable(${_name})
endfunction()

macro (IK_Export)
  cmake_parse_arguments("ARG" "TARGET" "" "DIRECTORIES" ${ARGN})
  message(STATUS "- export ${PROJECT_NAME} ${PROJECT_VERSION}")
  
  include(CMakePackageConfigHelpers)
  # generate the config file that is includes the exports
  configure_package_config_file(${PROJECT_SOURCE_DIR}/config/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${package_name}/cmake"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
  
  # generate the version file for the config file
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
  )

  # install the configuration file
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${package_name}/cmake"
  )
  
  foreach(dir ${ARG_DIRECTORIES})
    string(REGEX MATCH "(.*)/" prefix ${dir})
    if("${CMAKE_MATCH_1}" STREQUAL "")
      set(_destination "${package_name}")
    else()
      set(_destination "${package_name}/${CMAKE_MATCH_1}")
    endif()
    install(DIRECTORY ${dir} DESTINATION "${_destination}")
  endforeach()
  endmacro()