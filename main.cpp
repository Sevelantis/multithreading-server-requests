#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>

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
    for (int i = 0; i < resNum; i++)    resources[i] = new Resource();
    for (int i = 0; i < reqNum; i++)    requests[i] = new Request();

    // create main threads 
    bool running = true;
    std::thread threadExit(checkExit, std::ref(running));
    std::thread threadScreen(updateScreen, ref(running), ref(resources));
    
    // TODO run threads

    // join threads
    threadExit.join();
    threadScreen.join();

    // clear memory
    for (int i = 0; i < reqNum; i++)    delete requests[i];
    for (int i = 0; i < resNum; i++)    delete resources[i];
    
    // quit ncurses
    endwin();
}
std::mutex screen_mtx;
void updateScreen(bool &running, vector<Resource*>& pRes)
{
    while(running)
    {
        // screen_mtx.lock();
        for (int i = 0; i < resNum; i++)
        {
            int borderColor = 2;
            int idColor = 1;
            pRes[i]->draw(borderColor, idColor);
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        clear();
        // screen_mtx.unlock();
    }
    clear();
}

void checkExit(bool &running)
{
    bool isExit = false;
    while(!isExit)
    {
        // screen_mtx.lock();
        if(getch() == 'q')
            isExit = true;
        // screen_mtx.unlock();
    }
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

    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_RED);
    init_pair(8, COLOR_BLACK, COLOR_YELLOW);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
}