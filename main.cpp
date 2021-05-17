#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>

#include "request/Request.h"
#include "resource/Resource.h"

using namespace std;

// functions' definitions
void initNcurses();
void checkExit(bool &);
void updateScreen(bool &, vector<Resource*>&);

// variables
int reqNum = 5;
int resNum = 5;

int main()
{
    initNcurses();

    // create vector pointer objects
    vector<Request*> requests(reqNum);
    vector<Resource*> resources(resNum);

    // create objects
    for (int i = 0; i < reqNum; i++)    requests[i] = new Request();
    for (int i = 0; i < resNum; i++)    resources[i] = new Resource();

    // create main threads 
    bool running = true;
    std::thread threadExit(checkExit, std::ref(running));
    std::thread threadScreen(updateScreen, ref(running), ref(resources));
    
    // TODO run threads

    // join threads
    threadExit.join();
    threadScreen.join();

    // TODO clear memory
    
    // quit ncurses
    endwin();
}

void updateScreen(bool &running, vector<Resource*>& pRes)
{
    while(running)
    {
        clear();
        // display headers

        for (int i = 0; i < resNum; i++)
        {
            int color = 2;
            attron(COLOR_PAIR(color));
            //display
            pRes[i]->draw();
            // mvprintw(rows, cols, "%s", pRes[i]->getDrawing().c_str());
            attroff(COLOR_PAIR(color));
        }

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void checkExit(bool &running)
{
    while (getch() != 'q');

    running = false;
}

void initNcurses()
{
    initscr();
    noecho();
    start_color();
    init_pair(0, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
}