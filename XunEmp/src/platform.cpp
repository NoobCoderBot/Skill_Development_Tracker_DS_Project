#include "../include/platform.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

Platform GLOBAL_PLATFORM;

// Loads skill data and dependencies from a text file into the skill graph
bool Platform::loadSkillsFromFile(const string &path)
{
    ifstream in(path);
    if (!in)
    {
        cerr << "Cannot open: " << path << "\n";
        return false;
    }

    string line;
    bool deps = false;

    while (getline(in, line))
    {
        line = trim(line);
        if (line.empty())
            continue;
        if (line == "DEPENDENCIES")
        {
            deps = true;
            continue;
        }
        if (!deps)
            skills.addSkill(line);
        else
        {
            auto parts = split(line, ',');
            if (parts.size() >= 2)
                skills.addDependency(trim(parts[0]), trim(parts[1]));
        }
    }
    return true;
}

// Loads job listings from file and stores them in the job map
bool Platform::loadJobsFromFile(const string &path)
{
    ifstream in(path);
    if (!in)
    {
        cerr << "Cannot open: " << path << "\n";
        return false;
    }

    string line;
    while (getline(in, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        auto parts = split(line, '|');
        if (parts.size() < 4)
            continue;

        Job j;
        j.id = parts[0];
        j.title = parts[1];
        j.region = parts[2];

        auto sk = split(parts[3], ',');
        for (auto &s : sk)
            j.skills.push_back(trim(s));

        jobs.addJob(j);
    }
    return true;
}

// Recommends jobs in a given region based on user’s learned skills
void Platform::recommend(const string &region) const
{
    auto regionJobsList = jobs.getJobsByRegion(region);
    if (regionJobsList.empty())
    {
        cout << "  No jobs available in region " << region << ".\n";
        return;
    }

    cout << "  Job Recommendations for Region: " << region << "\n";

    auto skillDemand = jobs.getSkillDemandForRegion(region);

    struct JobPriority
    {
        Job job;
        double matchRatio;
        int demandScore;
        double priority;
        vector<string> missing;
        int known;
        int total;
    };

    vector<JobPriority> jobScores;

    // Compute score for each job
    for (const auto &job : regionJobsList)
    {
        int total = job.skills.size();
        int known = 0;
        int demandScore = 0;
        vector<string> missing;

        for (const auto &s : job.skills)
        {
            if (user.knows(s))
                known++;
            else
                missing.push_back(s);

            if (skillDemand.count(s))
                demandScore += skillDemand.at(s);
        }

        double matchRatio = (double)known / total;
        double priority = 0.7 * demandScore + 0.3 * (matchRatio * 10);

        jobScores.push_back({job, matchRatio, demandScore, priority, missing, known, total});
    }

    // Sort and display results by priority
    sort(jobScores.begin(), jobScores.end(), [](const JobPriority &a, const JobPriority &b)
         { return a.priority > b.priority; });

    bool foundAny = false;
    for (const auto &jp : jobScores)
    {
        cout << fixed << setprecision(2);
        cout << "\n  " << jp.job.title
             << " (" << jp.job.region << ")\n";

        cout << "   Skills known: " << jp.known << "/" << jp.total
             << " | Demand score: " << jp.demandScore
             << " | Priority: " << jp.priority << "\n";

        if (jp.known == jp.total)
            cout << "    You are fully eligible for this job!\n";
        else if (jp.known > 0)
        {
            cout << "     Partial match — missing skills: ";
            for (size_t i = 0; i < jp.missing.size(); ++i)
            {
                cout << jp.missing[i];
                if (i + 1 < jp.missing.size())
                    cout << ", ";
            }
            cout << "\n";
        }
        else
            cout << "   No matching skills yet.\n";

        foundAny = true;
    }

    if (!foundAny)
        cout << " No suitable jobs found.\n";
}

// Displays top trending skills either globally or for a specific region
void Platform::trending(int k, const string &region) const
{
    if (region.empty())
    {
        auto top = Trending::topK(jobs.skillDemand, k);
        cout << "Top " << k << " Trending Skills (Global):\n";
        for (auto &p : top)
            cout << "  " << p.first << " (" << p.second << ")\n";
    }
    else
    {
        auto counts = jobs.getSkillDemandForRegion(region);
        auto top = Trending::topK(counts, k);
        cout << "Top " << k << " Trending Skills in " << region << ":\n";
        for (auto &p : top)
            cout << "  " << p.first << " (" << p.second << ")\n";
    }
}

// Displays the learning path for a given skill using graph traversal
void Platform::showPath(const string &skill) const
{
    auto path = skills.getLearningPath(skill);
    if (path.empty())
    {
        cout << "No path for " << skill << "\n";
        return;
    }

    cout << "Learning Path to '" << skill << "':\n";
    for (size_t i = 0; i < path.size(); ++i)
        cout << "  " << i + 1 << ". " << path[i] << "\n";
}

// Prints overall summary of all skills and job data
void Platform::printSummary() const
{
    skills.print();
    jobs.printSummary();
}

// Adds a new job from command line and saves it to jobs.txt
void Platform::addJobFromCLI(const string &line)
{
    auto parts = split(line, '|');
    if (parts.size() < 4)
    {
        cout << " Invalid format. Use: id|title|region|skill1,skill2,...\n";
        return;
    }

    Job j;
    j.id = trim(parts[0]);
    j.title = trim(parts[1]);
    j.region = trim(parts[2]);

    auto sk = split(parts[3], ',');
    for (auto &s : sk)
        j.skills.push_back(trim(s));

    jobs.addJob(j);

    ofstream out("data/jobs.txt", ios::app);
    if (!out)
    {
        cout << "  Could not open jobs.txt for writing.\n";
        return;
    }

    out << j.id << "|" << j.title << "|" << j.region << "|";
    for (size_t i = 0; i < j.skills.size(); ++i)
    {
        out << j.skills[i];
        if (i + 1 < j.skills.size())
            out << ",";
    }
    out << "\n";

    cout << "  Job added and saved: " << j.title << " (" << j.region << ")\n";
}

// Saves the user’s learned skills to a file
void Platform::saveState(const string &path) const
{
    ofstream out(path);
    if (!out)
    {
        cout << "Cannot save.\n";
        return;
    }
    user.save(out);
    cout << " Saved user progress.\n";
}

// Loads the user’s learned skills from a file
void Platform::loadState(const string &path)
{
    ifstream in(path);
    if (!in)
    {
        cout << "Cannot load.\n";
        return;
    }
    user.load(in);
    cout << " Loaded user progress.\n";
}

// Recommends unlearned but in-demand skills for a given region
void Platform::recommendForUser(const string &region, int k) const
{
    auto counts = jobs.getSkillDemandForRegion(region);

    vector<pair<string, int>> unlearned;
    for (auto &p : counts)
    {
        if (!user.knows(p.first))
            unlearned.push_back(p);
    }

    if (unlearned.empty())
    {
        cout << " You already know all skills in demand for " << region << "!\n";
        return;
    }

    sort(unlearned.begin(), unlearned.end(),
         [](auto &a, auto &b)
         { return a.second > b.second; });

    cout << " Personalized Recommendations for " << region << ":\n";
    int shown = 0;
    for (auto &p : unlearned)
    {
        if (shown >= k)
            break;
        shown++;
        cout << "  " << p.first << " (" << p.second << " jobs)\n";
    }

    if (shown == 0)
        cout << " No new skills to recommend.\n";
}
