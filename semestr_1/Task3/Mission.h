#ifndef Mission_H
#define Mission_H

#include <vector>
#include "Task.h"

class Mission
{
private:
    vector<Task*> tasks;

public:
    ~Mission();

public:
    int Count();
    Task *GetTask(int pos = -1);

    bool AddTask(Task *task, int pos = -1);
    bool RemoveTask(int pos = -1);
    bool SwapTasks(int fPos, int sPos);

    bool Correctness();

private:
    inline static const string headerStr = "Миссия";
    string missionName = "";

public:
    bool SetName(const string &value);

    string TasksListToString();

    string WriteToString();
    bool ReadFromString(const string &str);
};

#endif