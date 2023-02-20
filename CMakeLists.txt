cmake_minimum_required(VERSION 3.15)
project(Http)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Http_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Http_SOURCE_DIR}/CMake 
  ${Http_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Http_ExternalTarget)
    set(TargetFolders ${Http_TargetFolders})
    set(TargetName    ${Http_TargetName})
    set(TargetGroup   ${Http_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    add_subdirectory(Internal/ParserBase)
    add_subdirectory(Internal/Threads)
    add_subdirectory(Internal/Sockets)

    set(TargetFolders TRUE)
    set(TargetGroup )
    set(TargetName Http)
    set(Http_INCLUDE  ${Http_SOURCE_DIR})
    set(Http_LIBRARY  Http Html)
endif()

add_subdirectory(Http)
add_subdirectory(Html)

if (Http_BUILD_TEST)
    if (NOT Http_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
