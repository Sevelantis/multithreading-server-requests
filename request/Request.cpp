#include "Request.h"

using namespace std;

void Request::run()
{
    while(alive)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(clockRate));
    }
}

Request::Request()
{
    
}

void Request::start()
{
    this->thr = thread(&Request::run, this);
}

Request::~Request()
{
    
}

void Request::kill()
{
    
}
