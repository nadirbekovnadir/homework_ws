#include "Task.h"
#include <sstream>
#include <regex>

// // // Task

string Task::GetHeader()
{
    return headerStr;
}

const Task *Task::Pointer() const
{
    return this;
}

Task::TaskType Task::Type() const
{
    return EmptyTask;
}

string Task::WriteToString() const
{
    return headerStr + "\n";
}

bool Task::ReadFromString(const string &str)
{
    return true;
}

// // // // // //

// // // Dive

Dive::ErrorState Dive::SetMaxMinDepth(float max, float min)
{
    if (max < 0 || min < 0)
        return AboveZero;

    if (max < min)
        return MaxLessThenMin;

    maxDepth = max;
    minDepth = min;

    return None;
}

Dive::ErrorState Dive::SetDepth(float value)
{
    if (value < minDepth || value > maxDepth)
        return OutOfBounds;

    depth = value;

    return None;
}

Dive::ErrorState Dive::SetMeasurementType(Dive::MeasurementType type)
{
    mType = type;
    return None;
}

Dive::ErrorState Dive::SetDiveType(Dive::DiveType type)
{
    dType = type;
    return None;
}

void Dive::GetMaxMinDepth(float &max, float &min)
{
    max = maxDepth;
    min = minDepth;
}

float Dive::GetDepth()
{
    return depth;
}

Dive::MeasurementType Dive::GetMeasurementType()
{
    return mType;
}

Dive::DiveType Dive::GetDiveType()
{
    return dType;
}

string Dive::GetHeader()
{
    return headerStr;
}

const Dive *Dive::Pointer() const
{
    return this;
}

Dive::TaskType Dive::Type() const
{
    return DiveTask;
}

string Dive::WriteToString() const
{
    string result;
    result.reserve(40);

    result += headerStr + ":\n";

    result += '\t' + trajectoryStr + " = ";

    if (dType == Vertical)
        result += verticalStr + '\n';
    else
        result += spiralStr + '\n';

    result += '\t' + measTypeStr + " = ";

    if (mType == ByDepthSensor)
        result += byDepthStr + '\n';
    else
        result += bySonarStr + '\n';

    result += '\t' + distanceStr + " = ";

    std::ostringstream value;
    value << std::fixed;
    value.precision(5);
    value << depth;

    result += value.str() + '\n';

    return result;
}

bool Dive::ReadFromString(const string &str)
{
    int pos = str.find(headerStr);
    if (pos == string::npos)
        return false;

    regex rgx;
    smatch m;

    rgx = trajectoryStr + "\\W+" +
          "(" + verticalStr + "|" + spiralStr + ")";

    if (!regex_search(str, m, rgx))
        return false;

    if (m[1].str() == verticalStr)
        dType = Vertical;
    else
        dType = Spirally;

    rgx = measTypeStr + "\\W+" +
          "(" + byDepthStr + "|" + bySonarStr + ")";

    if (!regex_search(str, m, rgx))
        return false;

    if (m[1].str() == byDepthStr)
        mType = ByDepthSensor;
    else
        mType = BySonar;

    rgx = distanceStr + "\\W+" + "(\\d+[.?]\\d*)";

    if (!regex_search(str, m, rgx))
        return false;

    depth = stof(m[1].str());

    return true;
}

// // // // // //

// // // Lift

string Lift::GetHeader()
{
    return headerStr;
}

const Lift *Lift::Pointer() const
{
    return this;
}

Lift::TaskType Lift::Type() const
{
    return LiftTask;
}

string Lift::WriteToString() const
{
    string writed = Dive::WriteToString();
    int pos = writed.find(Dive::GetHeader());
    writed.replace(pos, Dive::GetHeader().length(), headerStr);

    return writed;
}

bool Lift::ReadFromString(const string &str)
{
    int pos = str.find(headerStr);
    if (pos == string::npos)
        return false;

    string changed = str;
    changed.replace(
        pos, headerStr.length(), Dive::GetHeader());

    return Dive::ReadFromString(changed);
}

// // // // // //

// // // Move

Move::ErrorState Move::SetMaxMin(
    float maxX, float minX, float maxY, float minY)
{
    if (maxX < 0 || minX < 0 || maxY < 0 || minY < 0)
        return AboveZero;

    if (maxX < minX || maxY < minY)
        return MaxLessThenMin;

    Move::maxX = maxX;
    Move::minX = minX;

    Move::maxY = maxY;
    Move::minY = minY;

    return None;
}

Move::ErrorState Move::SetX(float value)
{
    if (value < minX || value > maxX)
        return OutOfBounds;

    x = value;
    return None;
}

Move::ErrorState Move::SetY(float value)
{
    if (value < minY || value > maxY)
        return OutOfBounds;

    y = value;
    return None;
}

Move::ErrorState Move::SetMovementType(Move::MovementType type)
{
    mType = type;
    return None;
}

Move::ErrorState Move::SetMovementControlType(
    Move::MovementControlType type)
{
    mcType = type;
    return None;
}

Move::ErrorState Move::SetPrecision(float value)
{
    //Про ограничения точности тишина...
    //Поэтому я просто сделаю их сам
    //Не особо думая...

    if (value > maxX / 2 || value > maxY / 2)
        return OutOfBounds;

    dr = value;
    return None;
}

void Move::GetXY(float &x, float &y)
{
    x = this->x;
    y = this->y;
}

Move::MovementType Move::GetMovementType()
{
    return mType;
}

Move::MovementControlType Move::GetMovementControlType()
{
    return mcType;
}

float Move::GetPrecision()
{
    return dr;
}

string Move::GetHeader()
{
    return headerStr;
}

const Move *Move::Pointer() const
{
    return this;
}

Move::TaskType Move::Type() const
{
    return MoveTask;
}

string Move::WriteToString() const
{
    string result;
    result.reserve(40);

    result += headerStr + ":\n";

    result += '\t' + controlStr + " = ";

    if (mcType == ByDepthSensor)
        result += byDepthStr + '\n';
    else
        result += bySonarStr + '\n';

    result += '\t' + movementStr + " = ";

    if (mType == InPoint)
        result += inPointStr + '\n';
    else
        result += alongLineStr + '\n';

    result += '\t' + pointStr + " = ";

    std::ostringstream value;
    value << std::fixed;
    value.precision(5);

    value << x;
    result += "(" + value.str() + ", ";

    value.str("");
    value << y;
    result += value.str() + ")\n";

    result += '\t' + precisStr + " = ";

    value.str("");
    value << dr;
    result += value.str() + "\n";

    return result;
}

bool Move::ReadFromString(const string &str)
{
    int pos = str.find(headerStr);
    if (pos == string::npos)
        return false;

    regex rgx;
    smatch m;

    rgx = controlStr + "\\W+" +
          "(" + byDepthStr + "|" + bySonarStr + ")";

    if (!regex_search(str, m, rgx))
        return false;

    if (m[1].str() == byDepthStr)
        mcType = ByDepthSensor;
    else
        mcType = BySonar;

    rgx = movementStr + "\\W+" +
          "(" + inPointStr + "|" + alongLineStr + ")";

    if (!regex_search(str, m, rgx))
        return false;

    if (m[1].str() == inPointStr)
        mType = InPoint;
    else
        mType = AlongLine;

    rgx = pointStr + "\\W+" +
          "(\\d+[.?]\\d*)" + "\\W+" + "(\\d+[.?]\\d*)";

    if (!regex_search(str, m, rgx))
        return false;

    x = stof(m[1].str());
    y = stof(m[2].str());

    rgx = precisStr + "\\W+" + "(\\d+[.?]\\d*)";

    if (!regex_search(str, m, rgx))
        return false;

    dr = stof(m[1].str());

    return true;
}

// // // // // //

// // // Return

string Return::GetHeader()
{
    return headerStr;
}

const Return *Return::Pointer() const
{
    return this;
}

Return::TaskType Return::Type() const
{
    return ReturnTask;
}

string Return::WriteToString() const
{
    return headerStr + "\n";
}

bool Return::ReadFromString(const string &str)
{
    int pos = str.find(headerStr);
    if (pos == string::npos)
        return false;

    return true;
}

// // // // // //