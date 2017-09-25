`gadhash`: Google Analytics Domain Hash Calculator
==================================================

Calculates Google Analytics domain hash given domain(s).

Overview
--------

When analyzing Google Analytics cookies, you will see an Urchin Tracking Module A (UTMA) value (utma=) in the URL. The part for comparison is only the number before the first dot ("."). For instance, in "utma=173272373.nnnnn...", the domain hash is 173272373 ("google.com", where n is any arbitrary number).

:warning: Enter only the domain (without the protocol, e.g., "`http://`") so that the domain hash will be calculated correctly. A hash value of 0 indicates an error.

This is a C++ CLI of [the Windows GUI C# version I wrote previously](https://github.com/danzek/google-analytics-domain-hash-calculator).

This uses `std::string` and assumes UTF-8 (POSIX)&mdash;I made no attempt to deal with wide characters (neither `std::wstring` nor `wchar_t`) to support Windows. I only intend for this to work on Linux.

Usage
-----

gadhash expects a file (or `stdin`) containing a list of domains separated by newlines (`\n`; *not* `\r`&mdash;be sure to use UNIX/LF line endings).

    gadhash [OPTIONS] [FILE(s)]

    Options:
      -h [ --help ]               get usage help
      -v [ --version ]            display version
      -d [ --delimiter ] arg (=,) specify delimiter string (comma/CSV by default;
                                  can be multiple characters)
      -f [ --file ] arg           file(s) containing list of domains (one per
                                  line); gadhash reads stdin if no file(s)
                                  specified or a hyphen ('-') is given

If no options or file names are specified, gadhash will read from `stdin`.

Contributing
------------

I welcome contributions. Contact me at d@4n68r.com, create and issue, and/or fork this code and create a pull request.

License, Disclaimers, etc.
--------------------------

Copyright &copy; 2017 Dan O'Day (d@4n68r.com)

This work is free. You can redistribute it and/or modify it under the terms of the Do What The Fuck You Want To Public License, Version 2, as published by Sam Hocevar. See the COPYING file for more details.

This project uses the `Boost` libraries for CLI argument parsing and memory-mapping files. Boost is distributed under the Boost Software License, Version 1.0 (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt).

The hash function is based on [a StackOverflow answer](https://stackoverflow.com/a/16243868/) posted by user [Nico Westerdale](https://stackoverflow.com/users/768732/nico-westerdale) to [this question](https://stackoverflow.com/q/4821627/) posted by user [Alex Wayne](https://stackoverflow.com/users/62076/alex-wayne) (the answer is written in C#). StackOverflow user contributions are licensed under [cc by-sa 3.0](https://creativecommons.org/licenses/by-sa/3.0/) with [attribution required](https://stackoverflow.blog/2009/06/25/attribution-required/).
