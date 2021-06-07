#ifndef P2_REQUEST_H
#define P2_REQUEST_H

#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include "../resource/Resource.h"
#include "../constants/Constants.h"

class Request
{
public:
    Request(int timeTotal, std::vector<std::pair<Resource*, int>>& tasks);
    ~Request();
    void start();
    void kill();

    int getColor();
    int getId();
    bool isFinished();
    void setFinished(bool finished);
    void finishTask(std::pair<Resource*, int> *pair, int i);
    void finishAllTasks();
    std::vector<std::string> getInfo();   
public:
    void lock();
    void unlock();
    void draw(int i);

private:
    static int idCntr;
    int id;
    std::thread thr;
    bool alive=true;
private:
    std::vector<std::pair<Resource*,int>> tasks;
    std::vector<bool> acquiredTasks;
    std::vector<bool> finishedTasks;
    std::vector<int> timesElapsed;
    int color;
    int yRow;
    std::mutex mtxMain;
    std::mutex mtxTime;
private:
    int clockRate=CLOCK_RATE;
    int timeTotal; // 1000-5000ms
    int resNum; //1-3
    bool finished=false;
private:
    void tryEating(std::pair<Resource*, int> *pair, int i);
    bool areAllTasksFinished();

    void run();
};

#endif //P2_REQUEST_H