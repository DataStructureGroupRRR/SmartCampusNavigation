// DepartmentUtil.h
// Purpose: Small string helpers used by the department module (trim, ASCII
//          case-insensitive compare, field splitting).
// Author: Rainier Velasco

#ifndef DEPARTMENT_UTIL_H
#define DEPARTMENT_UTIL_H

#include <string>
#include <vector>

namespace deptutil {
    // Removes leading/trailing spaces, tabs, carriage returns and newlines.
    std::string Trim(const std::string& s);

    // Returns a copy of s with ASCII letters converted to lowercase.
    std::string ToLower(const std::string& s);

    // True if a and b are equal ignoring ASCII capitalization (no trimming).
    bool EqualsIgnoreCase(const std::string& a, const std::string& b);

    // Splits line on delim and returns every field (an empty field is kept).
    std::vector<std::string> SplitFields(const std::string& line, char delim);
}

#endif // DEPARTMENT_UTIL_H
