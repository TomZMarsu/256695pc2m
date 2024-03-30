cmake_minimum_required(VERSION 3.5)

project(256695pc2M C)

#include(CTest)

function(PREPEND var )
   set(listVar "")
   foreach(f ${${var}})
       list(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
   endforeach(f)
   set(${var} "${listVar}" PARENT_SCOPE)
endfunction(PREPEND)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_subdirectory(src)
add_subdirectory(include)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_executable(256695pc2M ${skola_SRC} ${skola_HEADER})