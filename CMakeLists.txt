cmake_minimum_required(VERSION 3.16)

project(nativefiledialog LANGUAGES CXX C)

include_directories(.)
include_directories(./include)
include_directories(./src/include)

set(CMAKE_VERBOSE_MAKEFILE ON)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  add_compile_options(-fPIC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  add_compile_options(-fPIC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

add_library(nativefiledialog STATIC
  src/include/nfd.h
  src/common.h src/nfd_common.c src/nfd_common.h src/nfd_gtk.c src/nfd_win.cpp src/nfd_zenity.c src/simple_exec.h
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_library(nativefiledialog STATIC
      src/nfd_cocoa.m
  )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK REQUIRED gtk+-3.0)

    include_directories(${GTK_INCLUDE_DIRS})
    message("${GTK_INCLUDE_DIRS}")
    link_directories(${GTK_LIBRARY_DIRS})
    target_link_libraries(nativefiledialog ${GTK_LIBRARIES})
endif()

target_compile_definitions(nativefiledialog PRIVATE NATIVEFILEDIALOG_LIBRARY)
