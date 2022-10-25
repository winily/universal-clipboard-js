cmake_minimum_required(VERSION 3.0)
project(universal-clipboard-js LANGUAGES CXX)

enable_language(CXX)
enable_language(OBJC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_compile_options(-x objective-c++)
set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework AppKit -framework CoreData -framework Foundation")

find_library(COCOA_LIBRARY Cocoa)
if (NOT COCOA_LIBRARY)
  message(STATUS "Cocoa.framework NOT found!")
else()
  message(STATUS "Cocoa.framework found! ${COCOA_LIBRARY}")
endif()

find_library(APPKIT_LIBRARY AppKit)
if (NOT APPKIT_LIBRARY)
  message(STATUS "AppKit.framework NOT found!")
else()
  message(STATUS "AppKit.framework found! ${APPKIT_LIBRARY}")
endif()

find_library(FOUNDATION_LIBRARY Foundation)
if (NOT FOUNDATION_LIBRARY)
  message(STATUS "Foundation.framework NOT found!")
else()
  message(STATUS "Foundation.framework found! ${FOUNDATION_LIBRARY}")
endif()

include_directories(${CMAKE_JS_INC})

if(NOT EXISTS ../node-addon-api)
  include_directories(${CMAKE_CURRENT_LIST_FILE} ./node_modules/node-addon-api)
else()
  include_directories(${CMAKE_CURRENT_LIST_FILE} ../node-addon-api)
endif()

MESSAGE( STATUS "CMAKE_JS_INC = ${CMAKE_JS_INC}.")

set(SOURCES
  src/index.cpp
  src/mac.mm
)

# file(GLOB ALL_SRC "./src/*.hpp")
aux_source_directory(src ALL_SRC)
add_library(${PROJECT_NAME} SHARED ${ALL_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(universal-clipboard-js ${COCOA_LIBRARY})
target_link_libraries(universal-clipboard-js ${APPKIT_LIBRARY})
target_link_libraries(universal-clipboard-js ${FOUNDATION_LIBRARY})