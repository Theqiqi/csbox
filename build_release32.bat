@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86

cmake --preset=msvc-release-x86

cmake --build --preset=release-x86 -j8
pause
