#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>
#include <mutex>
#include "server/Server.h"

using namespace std;

// functions' definitions
void initNcurses();
void initRandomGenerator();
void checkExit(bool &);
void updateScreen(bool &, vector<Resource*>&, vector<Request*>&);

// variables
int resNum = 9;

int main()
{
    initNcurses();
    initRandomGenerator();

    Server *server = new Server(resNum);
    server->start();

    // create main threads 
    bool running = true;
    std::thread threadExit(checkExit, std::ref(running));
    std::thread threadScreen(updateScreen, ref(running), ref(server->getResources()), ref(server->getRequests()));
    //
    std::this_thread::sleep_for(std::chrono::milliseconds(555));
    
    server->spawnRequest();
    server->spawnRequest();
    server->spawnRequest();
    server->spawnRequest();

    // join threads
    threadExit.join();
    threadScreen.join();

    // clear memory
    server->kill();
    
    // quit ncurses
    endwin();
}

void updateScreen(bool &running, vector<Resource*>& pRes, vector<Request*>& pReq)
{
    while(running)
    {   
        // print requests header
        attron(COLOR_PAIR(GREEN_BLACK));
        mvprintw(Rectangle::Y_HEADER, Rectangle::X_HEADER, "Request[id]");
        mvprintw(Rectangle::Y_HEADER, Rectangle::X_HEADER_1, "Resource_1[id][%]");
        mvprintw(Rectangle::Y_HEADER, Rectangle::X_HEADER_2, "Resource_2[id][%]");
        mvprintw(Rectangle::Y_HEADER, Rectangle::X_HEADER_3, "Resource_3[id][%]");
        mvprintw(Rectangle::Y_HEADER, Rectangle::X_HEADER_4, "TimeTotal[ms]");
        attroff(COLOR_PAIR(GREEN_BLACK));attron(COLOR_PAIR(MAGENTA_BLACK));        
        mvprintw(Rectangle::Y_HEADER+1, Rectangle::X_HEADER, "_________________");
        mvprintw(Rectangle::Y_HEADER+1, Rectangle::X_HEADER_1, "_________________");
        mvprintw(Rectangle::Y_HEADER+1, Rectangle::X_HEADER_2, "_________________");
        mvprintw(Rectangle::Y_HEADER+1, Rectangle::X_HEADER_3, "_________________");
        mvprintw(Rectangle::Y_HEADER+1, Rectangle::X_HEADER_4, "_________________");
        attroff(COLOR_PAIR(MAGENTA_BLACK));

        // print resources rectangles
        for (int i = 0; i < resNum; i++)
        {
            pRes[i]->draw();
        }

        for (int i = 0; i < (int)pReq.size(); i++)
        {
            pReq[i]->draw(i);
        }
        
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(29));
        clear();
    }
    clear();
}

void checkExit(bool &running)
{
    bool isExit = false;
    while(!isExit)
    {
        if(getch() == 'q')
            isExit = true;
    }
    running = false;
}

void initNcurses()
{
    initscr();
    noecho();
    start_color();
    init_pair(YELLOW_WHITE, COLOR_YELLOW, COLOR_WHITE);
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_BLACK, COLOR_BLACK, COLOR_RED);
    init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);

    init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLACK_RED, COLOR_BLACK, COLOR_RED);
    init_pair(BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(BLACK_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
}

void initRandomGenerator()
{
    srand(time(NULL));
}