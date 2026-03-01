@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cmake --preset=msvc-dynamic

cmake --build --preset=debug -j8
pause