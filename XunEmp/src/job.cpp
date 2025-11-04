#include "../include/job.h"
#include <iostream>

// Adds a new job to the region-wise job map and updates global skill demand counts
void JobMap::addJob(const Job &j)
{
    regionJobs[j.region].push_back(j);
    for (auto &s : j.skills)
        skillDemand[s]++;
}

// Retrieves all jobs available in a specific region
std::vector<Job> JobMap::getJobsByRegion(const std::string &region) const
{
    auto it = regionJobs.find(region);
    if (it == regionJobs.end())
        return {};
    return it->second;
}

// Calculates and returns the frequency of required skills for a given region
std::unordered_map<std::string, int> JobMap::getSkillDemandForRegion(const std::string &region) const
{
    std::unordered_map<std::string, int> counts;
    auto it = regionJobs.find(region);
    if (it == regionJobs.end())
        return counts;
    for (auto &job : it->second)
        for (auto &s : job.skills)
            counts[s]++;
    return counts;
}

// Prints a summary of jobs by region and the overall global skill demand
void JobMap::printSummary() const
{
    std::cout << "Jobs by Region:\n";
    for (auto &p : regionJobs)
        std::cout << "  " << p.first << " : " << p.second.size() << " job(s)\n";

    std::cout << "Global Skill Demand:\n";
    for (auto &p : skillDemand)
        std::cout << "  " << p.first << " : " << p.second << "\n";
}
