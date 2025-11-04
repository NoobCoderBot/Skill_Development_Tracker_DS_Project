#include "../include/user.h"
#include <stack>
using namespace std;

// Adds a single skill to the user's learned skill set
void User::learnSkill(const string &skill)
{
    learnedSkills.insert(skill);
    cout << "--> Learned skill: " << skill << "\n";
}

// Adds a skill and all its prerequisite skills using reverse dependency traversal
void User::learnSkillWithPrereq(const string &skill, const unordered_map<string, vector<string>> &rev)
{
    unordered_set<string> visited;
    stack<string> st;
    st.push(skill);

    while (!st.empty())
    {
        string current = st.top();
        st.pop();

        if (visited.count(current))
            continue;
        visited.insert(current);

        if (learnedSkills.insert(current).second)
            cout << "--> Learned skill: " << current << "\n";

        auto it = rev.find(current);
        if (it != rev.end())
        {
            for (auto &pre : it->second)
                if (!visited.count(pre))
                    st.push(pre);
        }
    }
}

// Checks if the user already knows a given skill
bool User::knows(const string &skill) const
{
    return learnedSkills.count(skill) > 0;
}

// Displays all skills currently learned by the user
void User::showProgress() const
{
    if (learnedSkills.empty())
    {
        cout << "No skills learned yet.\n";
        return;
    }
    cout << " Learned Skills:\n";
    for (auto &s : learnedSkills)
        cout << "  - " << s << "\n";
}

// Saves the user's learned skills to an output stream (e.g., file)
void User::save(ostream &out) const
{
    for (auto &s : learnedSkills)
        out << s << "\n";
}

// Loads user's learned skills from an input stream (e.g., file)
void User::load(istream &in)
{
    learnedSkills.clear();
    string line;
    while (getline(in, line))
    {
        if (!line.empty())
            learnedSkills.insert(line);
    }
}
