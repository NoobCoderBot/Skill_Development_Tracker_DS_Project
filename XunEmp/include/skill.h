#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>
#include <unordered_map>

class SkillGraph
{
public:
    std::unordered_map<std::string, std::vector<std::string>> adj; // prereq -> dependents
    std::unordered_map<std::string, std::vector<std::string>> rev; // skill -> prereqs

    void addSkill(const std::string &name);
    void addDependency(const std::string &prereq, const std::string &skill);
    bool hasCycle() const;
    std::vector<std::string> getLearningPath(const std::string &target) const;
    void print() const;
};

#endif // SKILL_H
