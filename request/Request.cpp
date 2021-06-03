#include "Request.h"
#include <ncurses.h>
#include "../constants/Constants.h"
#include <algorithm>
#include "../randomGenerator/RandomGenerator.h"
#include "../rectangle/Rectangle.h"

int Request::idCntr = 0;

void Request::run()
{
    this->acquiredTasks.resize(resNum, false);
    this->finishedTasks.resize(resNum, false);
    this->timesElapsed.resize(resNum, timeTotal);
    while(alive)
    {
        int i = 0;
        // loop through all tasks
        for (auto pair : tasks)
        {
            // try to take the resource
            while(!acquiredTasks[i] && !finishedTasks[i])
            {
                pair.first->lock();
                tryEating(&pair, i);
                pair.first->unlock();
            }
            // eat resource until its finished
            if(acquiredTasks[i] && !finishedTasks[i])
                timesElapsed[i]-=clockRate/1000;
            
            if(timesElapsed[i] < 0)  // stop eating im full
            {
                pair.first->lock();
                finishTask(&pair, i);
                pair.first->unlock();
                
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
    // remove local task // no need 
    // removeTask(i); // ??

    // remove request from global resource
    pair->first->removeRequest(this, pair->second);

    // align time
    timesElapsed[i] = 0;

    // gather information
    finishedTasks[i] = true;
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

void Request::removeTask(int i)
{
    // tasks.erase(tasks.begin() + i);
    // this->resNum = tasks.size();
}

Request::Request(int timeTotal, std::vector<std::pair<Resource*,int>>& tasks)
{
    this->timeTotal = timeTotal;
    this->tasks = tasks;
    this->resNum = tasks.size();
    this->color = RandomGenerator::randInt(BLACK_BLUE, BLACK_MAGENTA+1); // <5, 10+1>
    this->id = idCntr++;
    this->yRow = Rectangle::Y_HEADER_VALUES;
    this->start();
}

int Request::getColor()
{
    return color;
}

int Request::getYRow()
{
    return yRow;
}

bool Request::isFinished()
{
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

int Request::getId()
{
    return id;
}

std::vector<std::string> Request::getInfo()
{
    std::vector<std::string> info(DATA_AMOUNT+3);
    std::string tmp="Request["+std::to_string(id)+"]";

    info[0] = tmp; // request id

    for (int i = 0; i < DATA_AMOUNT-1; i++)
    {
        std::string tmp="";
        if(i < (int)tasks.size())        // resources ids, percentages demands
        {
            int resId = tasks[i].first->getId();
            tmp.append("Resource["+std::to_string(resId)+"]");
            if(tasks[i].second == HALF)
                tmp.append("[50%]");
            else if(tasks[i].second == FULL)
                tmp.append("[100%]");
            info[i+5] = "["+std::to_string(timesElapsed[i])+"ms]";
        }
        else if(i < TASKS_AMOUNT)       // blank resources
        {
            tmp.append("---");
        }
        else if (i==TASKS_AMOUNT)       // time total
        {
            tmp.append("TimeTotal["+ std::to_string(timeTotal) + "ms]");
        }
        info[i+1] = tmp;
    }

    return info;
}

Request::~Request()
{
    
}

void Request::kill()
{
    this->alive = false;
    thr.join();
}

void Request::lock()
{
    displayMtx.lock();
}

void Request::unlock()
{
    displayMtx.unlock();
}

void Request::draw(int i)
{
    Rectangle::drawRequestInfo(this, i);
}
