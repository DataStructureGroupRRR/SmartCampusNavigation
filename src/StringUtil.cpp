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
