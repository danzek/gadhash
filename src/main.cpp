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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Concerning the use of Boost in this code:
 * Distributed under the Boost Software License, Version 1.0
 * (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/program_options.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>


/*!
 * Calculate Google Analytics domain hash
 *
 * @param [in] domain Domain to calculate hash for
 * @return int representing Google Analytics domain hash or 0 if error
 */
int hash(const std::string& domain)
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


/*!
 * Stream formatted output row given input row reference
 *
 * @param [in] delimiter delimiter to use for results output
 * @param [in] inputRow row from input stream containing domain
 * @param [out] output ostringstream to where output line + newline will be streamed
 */
void outputRow(const std::string& delimiter, const std::string& inputRow, std::ostringstream& output) {
    // todo: test to ensure newline char isn't being hashed from input row
    output << inputRow << delimiter << std::to_string(hash(inputRow)) << "\n";
}  // outputRow


/*!
 * Iterate over lines in istream input and stream parsed results to output
 *
 * @param input input stream containing list of domains to parse
 * @param delimiter delimiter to use for results output
 * @param [out] output output stringstream containing final parsed data for all domains
 */
void iterateLines(std::istream& input, const std::string& delimiter, std::ostringstream& output) {
    // iterate over file contents and stream parsed delimited results to output
    for (std::string line; std::getline(input, line); ) {
        outputRow(delimiter, line, output);
    }
}  // iterateLines


/*!
 * Read from stdin
 *
 * @param [in] delimiter delimiter to use for results output
 */
void readStdIn(const std::string& delimiter) {
    // allegedly improves performance, see https://stackoverflow.com/a/9371717/8652014
    std::ios_base::sync_with_stdio(false);

    // instantiate output stringstream and stream header row
    std::ostringstream output;
    output << "domain" << delimiter << "hash\n";

    // iterate over lines and generate output
    iterateLines(std::cin, delimiter, output);

    // stream final output to stdout
    std::cout << output.str();
} // readStdIn


/*!
 * Print version
 */
void printVersion() {
    std::cout << "Google Analytics Domain Hash Calculator v0.2" << "\n";
    std::cout << "Copyright (C) 2017 Dan O'Day <d@4n68r.com>\n\n";

    std::cout << "This work is free. You can redistribute it and/or modify it under the\n" \
                 "terms of the Do What The Fuck You Want To Public License, Version 2,\n" \
                 "as published by Sam Hocevar. See the COPYING file in the gadhash\n" \
                 "distribution for more details.\n\n";
} // printVersion

/*!
 * Print usage
 */
void printUsage() {
    std::cout << "When analyzing Google Analytics cookies, you will see an Urchin Tracking\n"  \
                 "Module A (UTMA) value (utma=) in the URL. The part for comparison is only\n" \
                 "the number before the first dot (\".\"). For instance, in \"utma=173272373.nnnnn...\",\n" \
                 "the domain hash is 173272373 (\"google.com\", where n is any arbitrary number).\n" \
                 "Enter the domain (without the protocol, i.e., don't include \"http://\", just use\n" \
                 "\"google.com\") and the domain hash will be calculated. A hash of 0 indicates an error.\n";
}  // printUsage


/*!
 * main
 */
int main(int argc, const char* argv[]) {
    try {
        std::string delimiter = ",";
        std::vector<std::string> files;
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
                ("help,h", "get usage help")
                ("version,v", "display version")
                ("delimiter,d", po::value<std::string>(&delimiter)->default_value(","),
                 "specify delimiter string (comma/CSV by default; can be multiple characters)")
                ("file,f", po::value<std::vector<std::string>>(&files),
                 "file(s) containing list of domains (one per line); gadhash reads stdin if no file(s) " \
                         "specified or a hyphen ('-') is given");

        po::positional_options_description posDesc;
        posDesc.add("file", -1);

        po::variables_map vm;

        try {
            po::store(po::command_line_parser(argc, argv).options(desc).positional(posDesc).run(), vm);

            // version info
            if (vm.count("version")) {
                printVersion();
                if (!vm.count("help")) {
                    // only exit if help not also requested
                    return EXIT_SUCCESS;
                }
            }

            // help option
            if (vm.count("help")) {
                printUsage();
                std::cout << '\n' << desc << '\n';
                return EXIT_SUCCESS;
            }

            // call notify after displaying version and/or help in case it finds error and throws exception
            po::notify(vm);

        } catch(po::error& e) {
            std::cerr << "ERROR: " << e.what() << '\n';
            std::cerr << desc << '\n';
            return EXIT_FAILURE;
        }

        // boost literal-escapes all user input (which is secure, but in this case I want a tab char)
        if (delimiter == "\\t") {
            delimiter = "\t";
        } else if (delimiter == "\\n") {  // I suppose someone could want a newline delimiter for some reason (consider)
            delimiter = "\n";
        }

        // read domain(s) from file(s)
        if (!files.empty()) {
            // instantiate output stringstream and stream header row
            std::ostringstream output;
            output << "domain" << delimiter << "hash\n";

            for (std::string& fn : files) {
                // handle if we encounter hyphen as file parameter
                if (fn == "-") {
                    if (files.size() > 1) {
                        std::cerr << "ERROR: Mixture of file name(s) and stdin specified. " \
                                     "Specify file name(s) OR stdin ('-').\n";
                        return EXIT_FAILURE;

                    } else {  // only one element in vector: '-' (read from stdin)
                        readStdIn(delimiter);
                        return EXIT_SUCCESS;
                    }
                }

                // memory map file for speed, files should be small enough to fit in RAM
                boost::iostreams::mapped_file_source f(fn);
                std::string fileContents(f.data(), f.size());
                f.close();

                // iterate over lines and generate output
                std::istringstream input(fileContents);
                iterateLines(input, delimiter, output);
            }

            // stream final output to stdout
            std::cout << output.str();

            return EXIT_SUCCESS;
        }

        // read domain(s) from stdin (default behavior)
        readStdIn(delimiter);

    } catch(std::exception& e) {
        std::cerr << "Unexpected error:\n" << e.what() << '\n'
                  << "If you're feeling helpful, email this error to Dan at d@4n68r.com and tell him what you tried.\n"
                  << "Or... you could just gripe and do nothing.";
        return EXIT_FAILURE;
    }

//    std::cout << std::endl;  // final buffer flush
    return EXIT_SUCCESS;
}  // main
