#include <iostream>
#include <string>
#include "../include/platform.h"
#include "../include/utils.h"

void help()
{
    std::cout << "Commands:\n"
              << "  load <skills.txt> <jobs.txt>\n"
              << "  summary\n"
              << "  path <skill>\n"
              << "  trending <k> [region]\n"
              << "  recommend <region>\n"
              << "  learn <skill>\n"
              << "  showprogress\n"
              << "  recommenduser <region> <k>\n"
              << "  addjob id|title|region|skills\n"
              << "  save <path>\n"
              << "  loadsave <path>\n"
              << "  exit\n";
}

int main()
{
    std::cout << "Skill Development Tracker (C++)\nType 'help' for commands.\n";
    std::string line;
    while (true)
    {
        std::cout << ">> ";
        if (!std::getline(std::cin, line))
            break;
        line = trim(line);
        if (line.empty())
            continue;
        auto parts = split(line, ' ');
        std::string cmd = parts[0];

        if (cmd == "exit")
            break;
        else if (cmd == "help")
            help();
        else if (cmd == "load")
        {
            if (parts.size() < 3)
            {
                std::cout << "Usage: load <skills> <jobs>\n";
                continue;
            }
            GLOBAL_PLATFORM.loadSkillsFromFile(parts[1]);
            GLOBAL_PLATFORM.loadJobsFromFile(parts[2]);
            std::cout << "Data loaded.\n";
        }
        else if (cmd == "summary")
            GLOBAL_PLATFORM.printSummary();
        else if (cmd == "path")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: path <skill>\n";
                continue;
            }
            GLOBAL_PLATFORM.showPath(parts[1]);
        }
        else if (cmd == "trending")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: trending <k> [region]\n";
                continue;
            }
            int k = std::stoi(parts[1]);
            if (parts.size() == 2)
                GLOBAL_PLATFORM.trending(k);
            else
                GLOBAL_PLATFORM.trending(k, parts[2]);
        }
        else if (cmd == "recommend")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: recommend <region>\n";
                continue;
            }
            GLOBAL_PLATFORM.recommend(parts[1]);
        }

        else if (cmd == "learn")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: learn <skill>\n";
                continue;
            }
            GLOBAL_PLATFORM.user.learnSkillWithPrereq(parts[1], GLOBAL_PLATFORM.skills.rev);
        }

        else if (cmd == "showprogress")
            GLOBAL_PLATFORM.user.showProgress();
        else if (cmd == "recommenduser")
        {
            if (parts.size() < 3)
            {
                std::cout << "Usage: recommenduser <region> <k>\n";
                continue;
            }
            GLOBAL_PLATFORM.recommendForUser(parts[1], std::stoi(parts[2]));
        }
        else if (cmd == "addjob")
        {
            std::string rest = line.substr(cmd.size() + 1);
            GLOBAL_PLATFORM.addJobFromCLI(rest);
        }
        else if (cmd == "save")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: save <path>\n";
                continue;
            }
            GLOBAL_PLATFORM.saveState(parts[1]);
        }
        else if (cmd == "loadsave")
        {
            if (parts.size() < 2)
            {
                std::cout << "Usage: loadsave <path>\n";
                continue;
            }
            GLOBAL_PLATFORM.loadState(parts[1]);
        }
        else
            std::cout << "Unknown command. Type 'help'.\n";
    }
}
