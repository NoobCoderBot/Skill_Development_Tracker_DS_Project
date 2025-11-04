#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>
#include <unordered_map>

class Trending
{
public:
    static std::vector<std::pair<std::string, int>> topK(const std::unordered_map<std::string, int> &counts, int k);
};

#endif // REGION_H
