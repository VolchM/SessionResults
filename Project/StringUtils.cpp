#include "StringUtils.hpp"


bool StringUtils::ContainsSpaces(const std::string& s) {
    for (char c : s) {
        if (isspace(c)) {
            return true;
        }
    }
    return false;
}

bool StringUtils::ConstainsSpacesOrEmpty(const std::string & s) {
    return ContainsSpaces(s) || s.size() == 0;
}

std::string StringUtils::Trim(const std::string& s) {
    int start = -1, end = -1;
    for (int i = 0; i < s.size(); i++) {
        if (!isspace(s[i])) {
            start = i;
        }
    }
    for (int i = s.size()-1; i >= 0; i--) {
        if (!isspace(s[i])) {
            end = i;
        }
    }
    return s.substr(start, end - start + 1);
}
