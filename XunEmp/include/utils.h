#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <cctype>

inline std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if (!item.empty())
            out.push_back(item);
    }
    return out;
}

inline std::string trim(const std::string &s)
{
    size_t a = 0;
    while (a < s.size() && std::isspace((unsigned char)s[a]))
        ++a;
    size_t b = s.size();
    while (b > a && std::isspace((unsigned char)s[b - 1]))
        --b;
    return s.substr(a, b - a);
}

#endif // UTILS_H
