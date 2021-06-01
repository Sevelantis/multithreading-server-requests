#include "Server.h"

using namespace std;

/*
*   request generator
*/
void Server::run()
{
    while(running)
    {
        if(isRequestSpawnReady())
            spawnRequest();

        std::this_thread::sleep_for(std::chrono::microseconds(clockRate));
    }
}

void Server::start()
{
    this->thr = thread(&Server::run, this);
}

void Server::createResources()
{
    resources.resize(resNum);
    for (int i = 0; i < resNum; i++)    resources[i] = new Resource();
}

bool Server::isRequestSpawnReady()
{
    if(requestSpawnTime++ >= requestSpawnTimeMax)
    {
        requestSpawnTime = 0;
        return true;
    }
    return false;
}

/*
*   create new request
*/
void Server::spawnRequest()
{
    // spawn random request:
    //  - 1s-5s
    //  - 1-3 zasoby (50 lub 100%)
}

Server::Server(int resNum)
{
    this->resNum = resNum;

    createResources();
}

std::vector<Resource*>& Server::getResources()
{
    return resources;
}

void Server::kill()
{

}

Server::~Server()
{
    
}
