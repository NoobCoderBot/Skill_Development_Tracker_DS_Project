#ifndef PLATFORM_H
#define PLATFORM_H

#include "skill.h"
#include "job.h"
#include "region.h"
#include "user.h"
#include "utils.h"
#include <string>

class Platform
{
public:
    SkillGraph skills;
    JobMap jobs;
    User user;

    bool loadSkillsFromFile(const std::string &path);
    bool loadJobsFromFile(const std::string &path);
    void recommend(const std::string &region) const;
    void trending(int k, const std::string &region = "") const;
    void showPath(const std::string &skill) const;
    void printSummary() const;

    void addJobFromCLI(const std::string &line);
    void saveState(const std::string &path) const;
    void loadState(const std::string &path);
    void recommendForUser(const std::string &region, int k) const;
};

extern Platform GLOBAL_PLATFORM;

#endif // PLATFORM_H
