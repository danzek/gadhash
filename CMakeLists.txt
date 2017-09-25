# Google Analytics Domain Hash Calculator
#
# Copyright (C) 2017 Dan O'Day <d@4n68r.com>
#
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See the COPYING file for more details.
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
