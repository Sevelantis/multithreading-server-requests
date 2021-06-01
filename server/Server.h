#ifndef P2_SERVER_H
#define P2_SERVER_H

#define CLOCK_RATE 30000

#include <vector>
#include <thread>
#include "../request/Request.h"
#include "../resource/Resource.h"

class Server
{
public:
    Server(int resNum);
    ~Server();
    
    void start();
    void kill();

    void spawnRequest();
    std::vector<Resource*>& getResources();

private:
    bool running=true;
    std::thread thr;
    std::vector<Request*> requests;
    std::vector<Resource*> resources;
    int resNum;
private:
    int clockRate=CLOCK_RATE;
    int requestSpawnTime=0;
    int requestSpawnTimeMax=200;
private:
    void run();
    void createResources();
    bool isRequestSpawnReady();
};


#endif //P2_SERVER_H