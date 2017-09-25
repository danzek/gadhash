# `gadhash`: Google Analytics Domain Hash Calculator

Calculates Google Analytics domain hash given domain(s).

### Contents

 - [Overview](#overview)
 - [Building](#building)
   - [Dependencies](#dependencies)
   - [CMake](#cmake)
 - [Usage](#usage)
 - [Contributing](#contributing)
 - [License, Disclaimers, etc.](#license-disclaimers-etc)

## Overview

When analyzing Google Analytics cookies, you will see an Urchin Tracking Module A (UTMA) value (utma=) in the URL. The part for comparison is only the number before the first dot ("."). For instance, in "utma=173272373.nnnnn...", the domain hash is 173272373 ("google.com", where n is any arbitrary number).

Enter only the domain (without the protocol, i.e. don't include "`http://`") so that the domain hash will be calculated correctly. A hash value of 0 indicates an error.

:warning: This uses `std::string` and assumes UTF-8 (POSIX)&mdash;I made no attempt to deal with wide characters (neither `std::wstring` nor `wchar_t`) nor alternate line endings (CR, i.e. `\r`) to support Windows. **I only intended for this to work on Linux.** That said, feel free to fork this code and make it support whatever you want it to!

This is a C++ CLI related to [the Windows GUI C# version I wrote previously](https://github.com/danzek/google-analytics-domain-hash-calculator).

## Building

`gadhash` has a single `main.cpp` file that contains all of the application code. As such, you can build the application using any compiler you are comfortable with that has C++11 support. CMake has been used to remain compiler-independent.

### Dependencies

The following **Boost 1.61.0 libraries** are ***required*** dependencies for `gadhash`:

 - Boost.Program_options
 - Boost.Iostreams

 See [the Boost documentation for getting started on *nix.](http://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html) (there is also [instructions for Windows](http://www.boost.org/doc/libs/1_61_0/more/getting_started/windows.html) but note that `gadhash` intentionally targets Linux platforms&mdash;I also wrote [a Windows GUI version](https://github.com/danzek/google-analytics-domain-hash-calculator), though, FYI).

### CMake

[Install CMake](https://cmake.org/install/) 3.8 or higher (if you don't already have it). This is a fairly new version so it may not be available in some package repositories. I recommend [downloading it from cmake.org](http://cmake.org/download/) and [following their installation instructions](https://cmake.org/install/).

Once you have CMake installed, you can generate a Makefile for your platform by invoking `cmake` and providing the path to the `CMakeLists.txt` file at the root of this repository. For example:

    cmake ~/Documents/gadhash/CMakeLists.txt

This will generate a Makefile which you can then use to build the software:

    make

This should result in a compiled binary being created for your system. You can also run `make install` if you choose to after this.

## Usage

gadhash expects a file (or `stdin`) containing a list of domains separated by newlines (`\n`; *not* `\r`&mdash;be sure to use UNIX/LF line endings).

    gadhash [OPTION(s)] [FILE(s)]

    Options:
      -h [ --help ]               get usage help
      -v [ --version ]            display version
      -d [ --delimiter ] arg (=,) specify delimiter string (comma/CSV by default;
                                  can be multiple characters)
      -f [ --file ] arg           file(s) containing list of domains (one per
                                  line); gadhash reads stdin if no file(s)
                                  specified or a hyphen ('-') is given

If no options or file names are specified, gadhash will read from `stdin`.

## Contributing

I welcome contributions. Contact me at d@4n68r.com, create an issue, and/or fork this code and create a pull request.

## License, Disclaimers, etc.

Copyright &copy; 2017 Dan O'Day (d@4n68r.com)

This work is free. You can redistribute it and/or modify it under the terms of the Do What The Fuck You Want To Public License, Version 2, as published by Sam Hocevar. See the COPYING file for more details.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This project uses the `Boost` libraries for CLI argument parsing and memory-mapping files. Boost is distributed under the Boost Software License, Version 1.0 (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

The hash function is based on [a StackOverflow answer](https://stackoverflow.com/a/16243868/) posted by user [Nico Westerdale](https://stackoverflow.com/users/768732/nico-westerdale) to [this question](https://stackoverflow.com/q/4821627/) posted by user [Alex Wayne](https://stackoverflow.com/users/62076/alex-wayne) (the answer is written in C#). StackOverflow user contributions are licensed under [cc by-sa 3.0](https://creativecommons.org/licenses/by-sa/3.0/) with [attribution required](https://stackoverflow.blog/2009/06/25/attribution-required/).
