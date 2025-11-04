#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

class User
{
public:
    std::unordered_set<std::string> learnedSkills;

    void learnSkill(const std::string &skill);
    bool knows(const std::string &skill) const;
    void showProgress() const;
    void save(std::ostream &out) const;
    void load(std::istream &in);
    void learnSkillWithPrereq(const std::string &skill, const std::unordered_map<std::string, std::vector<std::string>> &rev);
};

#endif // USER_H
