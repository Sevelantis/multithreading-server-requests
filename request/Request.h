#ifndef P2_REQUEST_H
#define P2_REQUEST_H

#define CLOCK_RATE 30000

#include <thread>

class Request
{
public:
    Request();
    ~Request();
    
    void start();
    void kill();

private:
    std::thread thr;

    bool alive=true;
    void run();
private:
    int clockRate=CLOCK_RATE;
};

#endif //P2_REQUEST_H