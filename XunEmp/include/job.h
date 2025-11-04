#ifndef JOB_H
#define JOB_H

#include <string>
#include <vector>
#include <unordered_map>

struct Job
{
    std::string id;
    std::string title;
    std::string region;
    std::vector<std::string> skills;
};

class JobMap
{
public:
    std::unordered_map<std::string, std::vector<Job>> regionJobs;
    std::unordered_map<std::string, int> skillDemand;

    void addJob(const Job &j);
    std::vector<Job> getJobsByRegion(const std::string &region) const;
    std::unordered_map<std::string, int> getSkillDemandForRegion(const std::string &region) const;
    void printSummary() const;
};

#endif // JOB_H
