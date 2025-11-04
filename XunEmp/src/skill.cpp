#include "../include/skill.h"
#include <iostream>
#include <unordered_set>
#include <functional>
using namespace std;

// Adds a new skill node to the graph if it doesn't already exist
void SkillGraph::addSkill(const string &name)
{
    if (adj.find(name) == adj.end())
        adj[name] = {};
    if (rev.find(name) == rev.end())
        rev[name] = {};
}

// Adds a directed edge representing a prerequisite relationship (prereq → skill)
void SkillGraph::addDependency(const string &prereq, const string &skill)
{
    addSkill(prereq);
    addSkill(skill);
    adj.at(prereq).push_back(skill);
    rev.at(skill).push_back(prereq);
}

// Detects if the skill dependency graph contains a cycle
bool SkillGraph::hasCycle() const
{
    unordered_map<string, int> state; // 0 = unvisited, 1 = visiting, 2 = visited
    for (auto &p : adj)
        state[p.first] = 0;

    function<bool(const string &)> dfs = [&](const string &u) -> bool
    {
        state[u] = 1;
        for (auto &v : adj.at(u))
        {
            if (state[v] == 1)
                return true;
            if (state[v] == 0 && dfs(v))
                return true;
        }
        state[u] = 2;
        return false;
    };

    for (auto &p : adj)
        if (state[p.first] == 0)
            if (dfs(p.first))
                return true;
    return false;
}

// Returns the full learning path (all prerequisites) for a given target skill
vector<string> SkillGraph::getLearningPath(const string &target) const
{
    vector<string> order;
    unordered_set<string> visited;

    function<void(const string &)> dfs = [&](const string &node)
    {
        if (visited.count(node))
            return;
        visited.insert(node);
        if (rev.find(node) != rev.end())
        {
            for (auto &pr : rev.at(node))
                dfs(pr);
        }
        order.push_back(node);
    };

    if (rev.find(target) == rev.end() && adj.find(target) == adj.end())
        return {target};

    dfs(target);
    return order;
}

// Prints the entire skill dependency graph (for debugging and visualization)
void SkillGraph::print() const
{
    cout << "Skill Graph (prereq -> dependents):\n";
    for (auto &p : adj)
    {
        cout << "  " << p.first << " -> ";
        for (size_t i = 0; i < p.second.size(); ++i)
            cout << p.second[i] << (i + 1 < p.second.size() ? ", " : "");
        cout << "\n";
    }
}
