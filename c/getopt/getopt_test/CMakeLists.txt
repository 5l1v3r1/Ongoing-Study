﻿cmake_minimum_required(VERSION 3.8)

project(getopt_test C)

add_executable(getopt_test "getopt_test.c")

# Currently, find_package does work with `getopt-win32` when using vcpkg.
if(WIN32)
    target_include_directories(getopt_test PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/include")
    target_link_libraries(getopt_test PRIVATE "$ENV{VCPKG_DIR}/installed/x86-windows/lib/getopt.lib")
    
    add_custom_command(TARGET getopt_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$ENV{VCPKG_DIR}/installed/x86-windows/bin/getopt.dll"
            $<TARGET_FILE_DIR:getopt_test>)
endif()


# References:
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
# https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
