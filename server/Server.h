#ifndef P2_SERVER_H
#define P2_SERVER_H

#include <vector>
#include <thread>
#include "../request/Request.h" // includes Resource.h

class Server
{
public:
    Server(int resNum);
    ~Server();
    
    void start();
    void kill();
    void spawnRequest();
    std::vector<Resource*>& getResources();
    std::vector<Request*>& getRequests();

private:
    bool running=true;
    std::thread thr;
    std::vector<Request*> requests;
    std::vector<Resource*> resources;
    int resNum;
private:
    int clockRate=CLOCK_RATE;
    int requestSpawnTime=0;
    int requestSpawnTimeMax=19;
private:
    void run();
    void createResources();
    bool isRequestSpawnReady();
    
    bool isDropRandomRequest(double prob);
    void dropRandomRequest();

    bool isDropAllRequests(double prob);
    void dropAllRequests();

private:
    void removeRequest(Request *pReq);
    void checkIfRequestFinished();

};


#endif //P2_SERVER_H