#include "Mission.h"
#include <malloc.h>
#include <sstream>
#include <iostream>
#include <locale>
#include <regex>
#include <string>

Mission::~Mission()
{
    // for (auto task : tasks)
    //     delete task;
}

int Mission::Count()
{
    return tasks.size();
}

Task *Mission::GetTask(int pos)
{
    if (pos < 0 || pos >= tasks.size())
        return nullptr;

    return tasks[pos];
}

bool Mission::AddTask(Task *task, int pos)
{
    if (pos < 0 && pos != -1)
        return false;

    if (pos == -1)
        tasks.push_back(task);
    else
    {
        auto iter = tasks.begin();
        tasks.insert(iter + pos, task);
    }

    return true;
}

bool Mission::RemoveTask(int pos)
{
    if (pos < 0 && pos != -1 ||
        pos >= tasks.size())
        return false;

    if (pos == -1)
    {
        delete *(--tasks.end());
        tasks.pop_back();
    }
    else
    {
        auto iter = tasks.begin();
        // auto pointer = (*iter)->Pointer();
        // delete pointer;
        tasks.erase(iter + pos);
    }

    return true;
}

bool Mission::SwapTasks(int fPos, int sPos)
{
    if (fPos < 0 && fPos != -1 ||
        fPos >= tasks.size())
        return false;

    if (sPos < 0 && sPos != -1 ||
        sPos >= tasks.size())
        return false;

    if (fPos == sPos)
        return true;

    swap(tasks[sPos], tasks[fPos]);

    return true;
}

bool Mission::Correctness()
{
    if (tasks.size() == 0)
        return true;

    auto iter = --tasks.end();
    if ((*iter)->Type() != Task::ReturnTask)
        return false;

    return true;
}

bool Mission::SetName(const string &value)
{
    for (auto ch : value)
        if (iswalpha(ch))
            return false;

    missionName = value;

    return true;
}

string Mission::TasksListToString()
{
    string result;
    result.reserve(10 * tasks.size());

    result += headerStr + " " + missionName + ":\n";

    if (tasks.size() == 0)
    {
        result += "Задачи отсутствуют\n";
        return result;
    }

    int pos = 0;
    // for (auto task : tasks)
    //     result += "[" + to_string(pos++) + "]"
    //     + task->Pointer()->GetHeader() + "\n"; // + "\n";

    for (auto task : tasks)
    {
        string header;

        switch (task->Type())
        {
        case Task::DiveTask:
            header = Dive::GetHeader();
            break;

        case Task::LiftTask:
            header = Lift::GetHeader();
            break;

        case Task::MoveTask:
            header = Move::GetHeader();
            break;

        case Task::ReturnTask:
            header = Return::GetHeader();
            break;

        default:
            header = Task::GetHeader();
            break;
        }

        result += "[" + to_string(pos++) + "]" +
                  header + "\n"; // + "\n";
    }

    result += "\n";

    return result;
}

string Mission::WriteToString()
{
    string result;
    result.reserve(35 * tasks.size());

    result += headerStr + " " + missionName + ":\n";

    if (tasks.size() == 0)
    {
        result += "Задачи отсутствуют\n";
        return result;
    }

    for (auto task : tasks)
        result += task->WriteToString(); // + "\n";

    result += "\n";

    return result;
}

bool Mission::ReadFromString(const string &str)
{
    int pos = str.find(headerStr);
    if (pos == string::npos)
        return false;

    tasks.clear();
    missionName = "";

    regex rgx;
    smatch m;

    rgx = headerStr + string("\\s+([^:\\d]+)[:]");
    //auto namePattern = "\\s+([\u0410-\u044f]+)";
    //rgx = headerStr + namePattern;

    if (regex_search(str, m, rgx))
        missionName = m[1].str();

    rgx = Dive::GetHeader() + "|" +
          Lift::GetHeader() + "|" +
          Move::GetHeader() + "|" +
          Return::GetHeader();

    // if (!regex_search(str, m, rgx))
    //     return false;

    auto matchBegin = std::sregex_iterator(
        str.begin(), str.end(), rgx);
    auto matchEnd = std::sregex_iterator();
    Task *task = nullptr;
    string taskStr;

    for (auto matchIter = matchBegin;
         matchIter != matchEnd;)
    {
        string matchStr = (*matchIter).str();

        if (matchStr == Dive::GetHeader())
            task = new Dive();

        if (matchStr == Lift::GetHeader())
            task = new Lift();

        if (matchStr == Move::GetHeader())
            task = new Move();

        if (matchStr == Return::GetHeader())
            task = new Return();

        string::const_iterator beginStrIter =
            (*matchIter).suffix().first;

        matchIter++;
        string::const_iterator endStrIter = str.cend();
        if (matchIter != matchEnd)
            endStrIter = (*matchIter).prefix().second;

        taskStr = matchStr + string(beginStrIter, endStrIter);

        if (!task->ReadFromString(taskStr))
            return false;

        tasks.push_back(task);
    }

    return true;
}