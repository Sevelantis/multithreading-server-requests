# Multi Threading
C++ project for educational purposes - multithreading using C++ - server-requests-resources. 

## Project environment settings
- Linux Ubuntu 20.04
- VS Code with a bunch of handy extensions
- g++ compiler
- ncurses library for better visualisation
- In order to build binary executable file **properly**, there is a need to set appropriate flags *on the end* of compiling command(take a look at file tasks.json):
  - /usr/bin/g++ -g ${file} -o ${fileDirname}/${fileBasenameNoExtension} **-pthread -lncurses**

## HOW TO RUN
```
git clone https://github.com/Sevelantis/multithreading-server-requests
```
```
cd multithreading-server-requests/
```
```
g++ -g main.cpp $PWD/rectangle/Rectangle.cpp $PWD/request/Request.cpp $PWD/resource/Resource.cpp $PWD/server/Server.cpp $PWD/randomGenerator/RandomGenerator.h -o main -Wall -pthread -lncurses
```
NOTE::(Please enter full screen mode)
```
./main
```

### example run 

![Alt text](/readme-files/example.gif?raw=true "program run")
