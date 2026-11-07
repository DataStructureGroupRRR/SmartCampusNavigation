#include "StringUtil.h"

using namespace std;

int scn::CompareStrings(const string& s1, const string& s2) {
    int s1L = s1.length();
    int s2L = s2.length();

    int len = min(s1L, s2L);
    
    for (int i = 0; i < len; ++i) {
        if (s1.at(i) < s2.at(i)) {
            return -1;
        } else if (s1.at(i) > s2.at(i)) {
            return 1;
        }
    }

    if (s1L < s2L) {
        return -1;
    } else if (s1L > s2L) {
        return 1;
    } else {
        return 0;
    }
}

// Trims whitespace from both ends of the string
string scn::Trim(const string& s) {
    const char* ws = " \t\r\n\f\v";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) {
        return "";
    }
    size_t last = s.find_last_not_of(ws);
    return s.substr(start, last - start + 1);
}

// ASCII-only lowercase conversion
string scn::ToLowerAscii(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] += static_cast<char>(out[i] - 'A' + 'a');
        }
    }
    return result;
}

// ASCII-only uppercase conversion
string scn::ToUpperAscii(const string& s) {
    string result = s;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] -= static_cast<char>(result[i] - 'a' + 'A');
        }
    }
    return result;
}

// case insensitive string comparison
bool scn::EqualsIgnoreCase(const string& a, const string& b) {
    return ToLowerAscii(a) == ToLowerAscii(b);
}

// Splits a string into fields based on a delimiter, keeping empty fields
vector<string> scn::SplitFields(const string& line, char delim) {
    vector<string> fields;
    string current;
    for (size_t i = 0; i < line.length(); ++i) {
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

// A line is skipped if it is blank or the first non-whitespace character is '#'
bool scn:: IsBlankOrComment (const string& line){
    string t = Trim(line);

    return t.empty() || t[0] == '#';
    
}
