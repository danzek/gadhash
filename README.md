Google Analytics Domain Hash Calculator
=======================================

This is a C++ CLI of [the Windows GUI C# version I wrote previously](https://github.com/danzek/google-analytics-domain-hash-calculator).

This uses `std::string` and assumes UTF-8 (POSIX)&mdash;I made no attempt to deal with wide characters (neither `std::wstring` nor `wchar_t`) to support Windows. I only intended this to work on Linux.

This uses the `Boost` libraries for CLI argument parsing and memory-mapping files.
