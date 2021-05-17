#include <ncurses.h>
#include <thread>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

// functions' definitions
void initNcurses();
void checkExit(bool &);
void updateScreen(bool &);

// variables
int N = 5;

int main()
{
    initNcurses();

    // TODO create threads 
    bool running = true;
    std::thread threadExit(checkExit, std::ref(running));
    std::thread threadScreen(updateScreen, std::ref(running));
    
    // TODO run threads

    // join threads
    threadExit.join();
    threadScreen.join();

    // TODO clear memory
    
    // quit ncurses
    endwin();
}

void updateScreen(bool &running)
{
    while(running)
    {
        clear();
        int rows = 4;
        int cols = 4;
        // display headers

        for (int i = 0; i < N; i++,rows+=4)
        {
            int color = 2;
            attron(COLOR_PAIR(color));
            //display
            mvprintw(rows, cols, "%s", "test");
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