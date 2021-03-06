cmake_minimum_required(VERSION 3.9)

project(findsodium_test)

file(DOWNLOAD
    "https://raw.githubusercontent.com/jedisct1/libsodium/master/contrib/Findsodium.cmake"
    "${CMAKE_BINARY_DIR}/Findsodium.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})

message(STATUS "========================================")

find_package(sodium QUIET)

message(STATUS "sodium_FOUND: ${sodium_FOUND}")
message(STATUS "sodium_VERSION: ${sodium_VERSION}")
message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
message(STATUS "sodium_LIBRARY_DEBUG: ${sodium_LIBRARY_DEBUG}")
message(STATUS "sodium_LIBRARY_RELEASE: ${sodium_LIBRARY_RELEASE}")
message(STATUS "sodium_DLL_DEBUG: ${sodium_DLL_DEBUG}")
message(STATUS "sodium_DLL_RELEASE: ${sodium_DLL_RELEASE}")

message(STATUS "========================================")

find_package(unofficial-sodium CONFIG REQUIRED)

message(STATUS "sodium_FOUND: ${sodium_FOUND}")
message(STATUS "sodium_VERSION: ${sodium_VERSION}")
message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
message(STATUS "sodium_LIBRARY_DEBUG: ${sodium_LIBRARY_DEBUG}")
message(STATUS "sodium_LIBRARY_RELEASE: ${sodium_LIBRARY_RELEASE}")
message(STATUS "sodium_LIBRARIES: ${sodium_LIBRARIES}")
message(STATUS "sodium_DLL_DEBUG: ${sodium_DLL_DEBUG}")
message(STATUS "sodium_DLL_RELEASE: ${sodium_DLL_RELEASE}")

message(STATUS "========================================")

find_library(sodium_LIBRARY_VIA_libsodium libsodium)

if (sodium_LIBRARY_VIA_libsodium)
    message(STATUS "sodium_LIBRARY_VIA_libsodium: ${sodium_LIBRARY_VIA_libsodium}")
endif ()

message(STATUS "========================================")

find_library(sodium_LIBRARY_VIA_sodium sodium)

if (sodium_LIBRARY_VIA_sodium)
    message(STATUS "sodium_LIBRARY_VIA_sodium: ${sodium_LIBRARY_VIA_sodium}")
endif ()

