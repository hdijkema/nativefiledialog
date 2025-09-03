cmake_minimum_required(VERSION 3.16)

project(nativefiledialog LANGUAGES CXX C)

include_directories(.)
include_directories(./include)
include_directories(./src/include)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(nativefiledialog STATIC
  src/include/nfd.h
  src/common.h src/nfd_common.c src/nfd_common.h src/nfd_gtk.c src/nfd_win.cpp src/nfd_zenity.c src/simple_exec.h
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_library(nativefiledialog STATIC
      src/nfd_cocoa.m
  )
endif()

target_compile_definitions(nativefiledialog PRIVATE NATIVEFILEDIALOG_LIBRARY)
