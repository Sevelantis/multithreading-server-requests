#include "Server.h"
#include <algorithm>
#include "../randomGenerator/RandomGenerator.h"

using namespace std;

/*
*   request generator thread run
*/
void Server::run()
{
    while(running)
    {
        if(isRequestSpawnReady())
            spawnRequest();

        else if(isDropAllRequests(.0003))
            dropAllRequests();

        else if(isDropRandomRequest(.0024))
            dropRandomRequest();
        
        // check if a request finished
        checkIfRequestFinished();

        std::this_thread::sleep_for(std::chrono::microseconds(clockRate));
    }
}

/*
*   create new request
*/
void Server::spawnRequest()
{
    /* 
    * requests need different resources
    * first: resources
    * second: demand for resource {50% | 100%}->{HALF | FULL}
    */
    std::vector<std::pair<Resource*,int>> tasks;
    
    // how long those resources are needed? (1000-5000) [ms]
    int time = RandomGenerator::randInt(500, 2000);

    // how many resources are needed?
    // {(1->40%), (2->40%), (3->20%)}
    int resourceDemandNum = RandomGenerator::randNumOfResources(.4, .4, .2);

    // which resources are needed?
    vector<int> resIds(resourceDemandNum, -1);
    for (int i = 0; i < resourceDemandNum; i++)
    {
        // get random resources' id's, but dont repeat them
        int id = RandomGenerator::randInt(0, resNum); // <0, resNum-1>
        while(std::find(resIds.begin(), resIds.end(), id) != resIds.end())
        {   // id repeats, search new
            id = RandomGenerator::randInt(0, resNum); // <0, resNum-1>
        }
        resIds[i] = id;

        // does the request need 50% of resource, or 100%? {50% | 100%}->{HALF | FULL}
        // probabilties: {{HALF -> 90%%}, {FULL -> 10}}
        int halfOrFull = RandomGenerator::randHalfOrFull(.9, .1);

        // add resource to request 
        tasks.push_back(std::make_pair(resources[id], halfOrFull));
    }

    Request *req = new Request(time, tasks);
    // mtxRequests.lock();
    requests.push_back(req);
    // mtxRequests.unlock();

    Rectangle::Y_HEADER_VALUES+=4;
}

Server::Server(int resNum)
{
    this->resNum = resNum;
    createResources();
}

void Server::removeRequest(Request *pReq)
{
    pReq->kill();
    requests.erase(std::remove(requests.begin(), requests.end(), pReq), requests.end());
    Rectangle::Y_HEADER_VALUES-=4;
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

std::vector<Resource*>& Server::getResources()
{
    return resources;
}

std::vector<Request*>& Server::getRequests()
{
    // std::lock_guard<std::mutex> guard(mtxRequests);
    return requests;
}

void Server::checkIfRequestFinished()
{
    // std::lock_guard<std::mutex> guard(mtxRequests);
    for(auto req : requests)
    {
        if(req->isFinished())
        {
            removeRequest(req);
            return;
        }
    }
}

void Server::kill()
{
    this->running = false;
    thr.join();
}

Server::~Server()
{
    
}

bool Server::isDropRandomRequest(double prob)
{
    return RandomGenerator::isProbability(prob);
}

void Server::dropRandomRequest()
{
    int size = requests.size();

    if(size == 0) return;
    int randIdx = RandomGenerator::randInt(0, size);
    requests[randIdx]->finishAllTasks();
}

bool Server::isDropAllRequests(double prob)
{
    return RandomGenerator::isProbability(prob);
}

void Server::dropAllRequests()
{
    int size = requests.size();

    if(size == 0) return;

    for(auto req : requests)
        req->finishAllTasks();

    requestSpawnTime=-250;
}