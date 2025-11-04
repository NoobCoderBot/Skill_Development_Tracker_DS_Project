#include "../include/region.h"
#include <queue>
#include <utility>
using namespace std;

// Returns the top K most in-demand skills based on frequency using a max heap
vector<pair<string, int>> Trending::topK(const unordered_map<string, int> &counts, int k)
{
    using P = pair<int, string>;
    auto cmp = [](const P &a, const P &b)
    { return a.first < b.first; };

    priority_queue<P, vector<P>, decltype(cmp)> pq(cmp);

    for (auto &p : counts)
        pq.push({p.second, p.first});

    vector<pair<string, int>> out;
    for (int i = 0; i < k && !pq.empty(); ++i)
    {
        auto t = pq.top();
        pq.pop();
        out.push_back({t.second, t.first});
    }

    return out;
}
