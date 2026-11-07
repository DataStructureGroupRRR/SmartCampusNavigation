#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>


namespace scn {
    int CompareStrings(const std::string& s1, const std::string& s2);

    // Removes spaces, tabs, \r, \n, \f, \v from both ends
    std:: string Trim(const std::string& s);

    // ASCII-only case conversion. 
    std:: string ToLowerAscii (const std::string& s);
    std:: string ToUpperAscii (const std:: string& s);

    // True if a and b are equal ignoring ASCII capitalizaion
    bool EqualsIgnoreCase(const std:: string& a, const std::string& b);

    // Splits on delimiter, keeping empty fileds
    std:: vector<std::string> SplitFields(const std:: string& line, char delim);

    // True if the line is blank or first non whitespace char is #
    bool IsBlankOrComment(const std:: string& line);
}

#endif // STRING_UTIL_H
