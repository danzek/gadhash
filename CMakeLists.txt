# Google Analytics Domain Hash Calculator
#
# MIT License
#
# Copyright (c) 2017 Dan O'Day <d@4n68r.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Concerning the use of Boost in this code:
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.8)
project(gadhash)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/main.cpp)

# Boost: see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost 1.61.0 REQUIRED COMPONENTS program_options iostreams)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(gadhash ${SOURCE_FILES})
    target_link_libraries(gadhash ${Boost_LIBRARIES})
endif()
