#include "Request.h"
#include <ncurses.h>
#include "../constants/Constants.h"
#include <algorithm>
#include "../randomGenerator/RandomGenerator.h"
#include "../rectangle/Rectangle.h"

int Request::idCntr = 0;

void Request::run()
{
    while(alive)
    {
        int i = 0;
        // loop through all tasks
        for (auto task : tasks)
        {
            // try to take the resource
            if(!acquiredTasks[i] && !finishedTasks[i])
            {
                task.first->lock();
                tryEating(&task, i);
                task.first->unlock();
            }

            // eat resource until its finished
            if(acquiredTasks[i] && !finishedTasks[i])
            {
                mtxTime.lock();
                timesElapsed[i]-=20;
                mtxTime.unlock();
            }
            mtxTime.lock();
            int time = timesElapsed[i];
            mtxTime.unlock();
            if(time < 0)  // stop eating im full
            {
                task.first->lock();
                finishTask(&task, i);
                task.first->unlock();
                
                // check if all tasks are finished
                if(areAllTasksFinished())
                {
                    this->finished = true;
                }
            }
            i++;
            std::this_thread::sleep_for(std::chrono::microseconds(clockRate));
        }
    }
}

void Request::finishTask(std::pair<Resource*, int> *pair, int i)
{
    // remove request from global resource
    pair->first->removeRequest(this, pair->second);

    // align time
    mtxTime.lock();
    timesElapsed[i] = 0;
    mtxTime.unlock();

    // gather information
    finishedTasks[i] = true;
}

void Request::finishAllTasks()
{
    int i = 0;
    mtxMain.lock();
    for(auto task : tasks)
    {
        task.first->lock();
        task.first->removeRequest(this, task.second);
        task.first->unlock();

        mtxTime.lock();
        if(!timesElapsed.empty())
            timesElapsed[i] = 0;
        mtxTime.unlock();
        finishedTasks[i] = true;
        i++;
    }
    this->setFinished(true);
    mtxMain.unlock();
}

void Request::tryEating(std::pair<Resource*, int> *pair, int i)
{
    // case resource is 0%
    if (NONE == pair->first->getState())
    {
        pair->first->addRequest(this, pair->second);
        acquiredTasks[i] = true;
    }
    // case resource is 50%
    else if (HALF == pair->first->getState() && pair->second == HALF)
    {
        pair->first->addRequest(this, HALF2);
        acquiredTasks[i] = true;
    }
}

bool Request::areAllTasksFinished()
{
    return std::find(finishedTasks.begin(), finishedTasks.end(), false) == finishedTasks.end();
}

Request::Request(int timeTotal, std::vector<std::pair<Resource*,int>>& tasks)
{
    this->timeTotal = timeTotal;
    this->tasks = tasks;
    this->resNum = tasks.size();
    this->color = RandomGenerator::randInt(BLACK_BLUE, BLACK_MAGENTA+1); // <5, 10+1>
    this->id = idCntr++;
    mtxTime.lock();
    this->acquiredTasks.resize(resNum, false);
    this->finishedTasks.resize(resNum, false);
    this->timesElapsed.resize(resNum, timeTotal);
    mtxTime.unlock();
    this->start();
}

int Request::getColor()
{
    // std::lock_guard<std::mutex> guard(mtx);
    return color;
}


bool Request::isFinished()
{
    // std::lock_guard<std::mutex> guard(mtxMain);
    return finished;
}

void Request::setFinished(bool finished)
{
    this->finished = finished;
}

void Request::start()
{
    this->thr = std::thread(&Request::run, this);
}

Request::~Request()
{
    
}

void Request::lock()
{
    mtxMain.lock();
}

void Request::unlock()
{
    mtxMain.unlock();
}

void Request::draw(int i)
{
    Rectangle::drawRequestInfo(this, i);
}

std::vector<std::string> Request::getInfo()
{
    std::vector<std::string> info(DATA_AMOUNT+3);
    std::string tmp="Request["+std::to_string(id)+"]";

    info[0] = tmp; // request id

    for (int i = 0; i < DATA_AMOUNT-1; i++)
    {
        mtxMain.lock();
        std::string tmp="";
        int size = (int)tasks.size();
        if(size == 0) break;
        if(i < size)        // resources ids, percentages demands
        {
            int resId = tasks[i].first->getId();
            tmp.append("Resource["+std::to_string(resId)+"]");
            if(tasks[i].second == HALF)
                tmp.append("[50%]");
            else if(tasks[i].second == FULL)
                tmp.append("[100%]");

            int time = -1;
            mtxTime.lock();
            if(!timesElapsed.empty())
                time = timesElapsed[i];
            mtxTime.unlock();

            if(time == -1)
                info[i+5] = "[...]";
            else if(time != 0)
                info[i+5] = "["+std::to_string(time)+"]";
            else if(time == 0)
                info[i+5] = "[FINISHED]";
            
        }
        else if(i < TASKS_AMOUNT)       // blank resources
        {
            tmp.append("-----");
        }
        else if (i==TASKS_AMOUNT)       // time total
        {
            tmp.append("TimeTotal["+ std::to_string(timeTotal) + "ms]");
        }
        info[i+1] = tmp;
        mtxMain.unlock();
    }
    return info;
}

void Request::kill()
{
    mtxMain.lock();
    this->alive = false;
    thr.join();
    mtxMain.unlock();
}

int Request::getId()
{
    return id;
}
