#[[
Copyright (c) 2022 bipentihexium

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
]]

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(AB2)

include(CTest)

add_executable(ab2 ./main.cpp)
if(UNIX)
	target_link_libraries(ab2 pthread)
	set(WARN_OPTIONS -Wall -Wextra -Wpedantic)
elseif(MINGW)
	target_link_libraries(ab2 winpthread)
	set(WARN_OPTIONS -Wall -Wextra -Wpedantic)
elseif(WIN32)
	#target_link_libraries(ab2 )
	set(WARN_OPTIONS /W4)
else()
	set(WARN_OPTIONS )
endif()
add_compile_options(ab2 ${WARN_OPTIONS})

enable_testing()
add_executable(ab2_test_mach0 ./tests/test_mach0.cpp)
add_compile_options(ab2_test_mach0 ${WARN_OPTIONS})
add_test(NAME machine_no_key COMMAND $<TARGET_FILE:ab2_test_mach0>)
add_executable(ab2_test_mach1 ./tests/test_mach1.cpp)
add_compile_options(ab2_test_mach1 ${WARN_OPTIONS})
add_test(NAME machine_1_key COMMAND $<TARGET_FILE:ab2_test_mach1>)
add_executable(ab2_test_codegen ./tests/test_codegen.cpp)
add_compile_options(ab2_test_codegen ${WARN_OPTIONS})
add_test(NAME codegen COMMAND $<TARGET_FILE:ab2_test_codegen>)
