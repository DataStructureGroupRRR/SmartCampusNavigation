// DepartmentUtil.cpp
// Purpose: Implementation of the department module's string helpers.
// Author: Rainier Velasco

#include "DepartmentUtil.h"

using namespace std;

namespace deptutil {

// Removes leading/trailing whitespace, including '\r' from Windows line endings.
string Trim(const string& s) {
    const string whitespace = " \t\r\n\f\v";
    size_t first = s.find_first_not_of(whitespace);
    if (first == string::npos) {
        return "";
    }
    size_t last = s.find_last_not_of(whitespace);
    return s.substr(first, last - first + 1);
}

// Converts ASCII letters to lowercase; other characters are unchanged.
string ToLower(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = static_cast<char>(result[i] - 'A' + 'a');
        }
    }
    return result;
}

// Compares two strings ignoring ASCII capitalization.
bool EqualsIgnoreCase(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return false;
    }
    return ToLower(a) == ToLower(b);
}

// Splits on delim, keeping empty fields ("a||b" gives 3 fields).
vector<string> SplitFields(const string& line, char delim) {
    vector<string> fields;
    string current;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == delim) {
            fields.push_back(current);
            current.clear();
        } else {
            current += line[i];
        }
    }
    fields.push_back(current);
    return fields;
}

} // namespace deptutil
