# MultiThreading1
C++ project for educational purposes - multithreading in C++ - server-requests-resources. 

Student: Miron Oskroba
year, semester: III, 6
Course: Operating Systems 2

## Project environment settings
- Linux Ubuntu 20.04
- VS Code with a bunch of handy extensions
- g++ compiler
- ncurses library for better visualisation
- In order to build binary executable file **properly**, there is a need to set appropriate flags *on the end* of compiling command(take a look at file tasks.json):
  - /usr/bin/g++ -g ${file} -o ${fileDirname}/${fileBasenameNoExtension} **-pthread -lncurses**

### example run

![Alt text](/readme-files/program-run.gif?raw=true "program run")
