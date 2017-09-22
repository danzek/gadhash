/*! Google Analytics Domain Hash Calculator
 *
 * When analyzing Google Analytics cookies, you will see an Urchin Tracking Module A (UTMA)
 * value (utma=) in the URL. The part for comparison is only the number before the first dot
 * ("."). For instance, in "utma=173272373.nnnnn...", the domain hash is 173272373
 * ("google.com", where n is any arbitrary number). Enter the domain (without the protocol,
 * i.e., don't include "http://", just use "google.com") and the domain hash will be calculated.
 *
 * Copyright (C) 2017 Dan O'Day <d@4n68r.com>
 *
 * This work is free. You can redistribute it and/or modify it under the terms of the Do What
 * The Fuck You Want To Public License, Version 2, as published by Sam Hocevar. See the COPYING
 * file for more details.
 *
 * Concerning the use of Boost in this code:
 * Distributed under the Boost Software License, Version 1.0
 * (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

#include <iostream>

/*!
 * Calculate Google Analytics domain hash
 *
 * @param [in] domain Domain to calculate hash for
 * @return int representing Google Analytics domain hash or 0 if error
 */
int hash(std::string domain)
{
    int a = 1;
    int c = 0;
    int h, o;
    if (!domain.empty()) {
        a = 0;

        // domain.length() returns an ulong which could overflow h (int)
        // check for unlikely event of int overflow here and return 0 to prevent
        if (domain.length() > INT_MAX) {
            return 0;
        }

        for (h = domain.length() - 1; h >= 0; h--) {
            o = domain[h];
            a = (a << 6 & 268435455) + o + (o << 14);
            c = a & 266338304;
            a = c != 0 ? a ^ c >> 21 : a;
        }
    }

    return a;
}  // hash

/*
 * Print version
 */
void printVersion() {
    std::cout << "Google Analytics Domain Hash Calculator v0.2" << "\n";
} // printVersion

/*
 * Print usage
 */
void printUsage() {
    std::cout << "When analyzing Google Analytics cookies, you will see an Urchin Tracking"  \
                 "Module A (UTMA) value (utma=) in the URL. The part for comparison is only " \
                 "the number before the first dot (\".\"). For instance, in \"utma=173272373.nnnnn...\", " \
                 "the domain hash is 173272373 (\"google.com\", where n is any arbitrary number). " \
                 "Enter the domain (without the protocol, i.e., don't include \"http://\", just use " \
                 "\"google.com\") and the domain hash will be calculated. A hash of 0 indicates an error.\n";
}  // printUsage

int main(int argc, const char* argv[]) {
    try {
        char delimiter = ',';
        std::vector<std::string> files;
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
                ("help,h", "get usage help")
                ("version,v", "display version")
                ("delimiter,d", po::value<char>(&delimiter)->default_value(','),
                 "specify printable ASCII delimiter (comma/CSV by default)")
                ("file,f", po::value<std::vector<std::string>>(&files),
                 "file containing list of domains (one per line); gadhash reads stdin if no file " \
                         "specified or a hyphen ('-') is given");

        po::positional_options_description posDesc;
        posDesc.add("file", -1);

        po::variables_map vm;

        try {
            po::store(po::command_line_parser(argc, argv).options(desc).positional(posDesc).run(), vm);

            // help option
            if (vm.count("help")) {
                printUsage();
                std::cout << '\n' << desc << '\n';
                return EXIT_SUCCESS;
            }

            // call notify after help in case it finds error and throws exception
            po::notify(vm);

        } catch(po::error& e) {
            std::cerr << "ERROR: " << e.what() << '\n';
            std::cerr << desc << '\n';
            return EXIT_FAILURE;
        }

        // handle args
        if (vm.count("version")) {
            printVersion();
        }

        if (delimiter != ',' && !isprint(delimiter)) {
            // needs to be printable ASCII char
            delimiter = ',';
        }

        // read domain(s)
        if (!files.empty()) {
            // read from file
            for (std::string fn : files) {
                std::cout << "file name: " << fn << '\n';  // debug only
            }
        } else {
            // read from stdin
            std::cout << "reading from stdin\n";  // debug only
        }

    } catch(std::exception& e) {
        std::cerr << "Unexpected error:\n" << e.what() << '\n'
                  << "If you're feeling helpful, email this error to Dan at d@4n68r.com and tell him what you tried.\n"
                  << "Or... you could just gripe and do nothing.";
        return EXIT_FAILURE;
    }

    std::cout << std::endl;  // final buffer flush
    return EXIT_SUCCESS;
}  // main
