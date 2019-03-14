vcpkg install gtest:x86-windows-static
vcpkg install roaring:x86-windows-static
mkdir build-x86-windows-static
cd build-x86-windows-static
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_GENERATOR_PLATFORM=Win32 -DUSE_MSVC_STATIC_RUNTIME=ON
cmake --build . --config Release
src\Release\roaring_bitmaps_tests.exe
cd ..
pause
