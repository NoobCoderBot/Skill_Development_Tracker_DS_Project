
# User Manual – Skill Development Tracker for Marginalized Groups

## Project Overview
The Skill Development Tracker is a C++ command-line application designed to help underprivileged youth identify and learn in-demand skills aligned with local job opportunities.
It uses Graphs, Hash Maps, Heaps, and Sets to provide intelligent, data-driven skill and job recommendations.
________________________________________
## System Requirements
•	Operating System: Linux / Windows (via WSL)
•	Compiler: g++ supporting C++17
•	Memory: Minimum 4 GB RAM
•	Files required:
o	data/skills.txt – contains skills and their prerequisites
o	data/jobs.txt – contains job listings and required skills
________________________________________
## Installation Steps
1.	Open a terminal and navigate to your project folder:
2.	cd SkillTracker
3.	Compile the project using the Makefile:
4.	make
(Or manually compile with g++ src/*.cpp -Iinclude -std=c++17 -o skill-tracker)
5.	Run the executable:
6.	./skill-tracker
________________________________________
## Key Features
•	Graph-based skill mapping – automatically adds all prerequisite skills.
•	Region-based job mapping – uses hash maps to suggest relevant jobs.
•	Heap-driven trending engine – recommends the most in-demand skills.
•	Data persistence – newly added jobs and progress are saved to files.
•	Personalized recommendations – jobs matched to the user’s learned skills.
________________________________________
## Available Commands
Command	                Description
load data/skills.txt data/jobs.txt	                Loads skill and job data
learn <SkillName>	                Adds a skill and all its prerequisites
recommend <Region>	                Recommends jobs user is eligible for in that region
recommenduser <Region> <N>	                Suggests top N trending skills in that region
`addjob <ID>	                Adds a new job to the jobs.txt
showprogress	                 Displays all learned skills
summary	                 Shows overview of loaded data
exit	                 Saves data and closes the program
________________________________________
## Troubleshooting
Issue	Possible Fix
Command not found	Ensure you are in the correct folder
make: not found	Install build tools: sudo apt install build-essential
File not found	Check file paths for skills.txt and jobs.txt
Program exits instantly	Run via terminal instead of double-clicking

