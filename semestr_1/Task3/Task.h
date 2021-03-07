#ifndef Task_H
#define Task_H

#include <string>

using namespace std;

class Task
{
public:
    enum TaskType
    {
        EmptyTask,
        DiveTask,
        LiftTask,
        MoveTask,
        ReturnTask
    };

    enum ErrorState
    {
        None,
        OutOfBounds,
        AboveZero,
        MaxLessThenMin
    };

private:
    inline static const string headerStr = "Пустое задание";

public:
    static string GetHeader();

    virtual const Task *Pointer() const;
    virtual TaskType Type() const;
    virtual string WriteToString() const;
    virtual bool ReadFromString(const string &str);
};

class Dive : public Task
{
public:
    enum MeasurementType
    {
        ByDepthSensor,
        BySonar
    };

    enum DiveType
    {
        Vertical,
        Spirally
    };

private:
    inline static float maxDepth = 100;
    inline static float minDepth = 0;

    float depth = 50;
    MeasurementType mType = ByDepthSensor;
    DiveType dType = Vertical;

public:
    static ErrorState SetMaxMinDepth(float max, float min);

    ErrorState SetDepth(float value);
    ErrorState SetMeasurementType(MeasurementType type);
    ErrorState SetDiveType(DiveType type);

    static void GetMaxMinDepth(float &max, float &min);

    float GetDepth();
    MeasurementType GetMeasurementType();
    DiveType GetDiveType();

private:
    inline static const string headerStr = "Погружениe";

    inline static const string trajectoryStr = "траектория";

    inline static const string verticalStr = "вертикальная";
    inline static const string spiralStr = "спиральная";

    inline static const string measTypeStr = "тип измерения";

    inline static const string byDepthStr = "по глубине";
    inline static const string bySonarStr = "по отстоянию";

    inline static const string distanceStr = "расстояние";

public:
    static string GetHeader();

    virtual const Dive *Pointer() const override;
    virtual TaskType Type() const override;
    virtual string WriteToString() const override;
    virtual bool ReadFromString(const string &str) override;
};

class Lift : public Dive
{
    inline static const string headerStr = "Всплытие";

public:
    static string GetHeader();

    const Lift *Pointer() const override;
    TaskType Type() const override;
    string WriteToString() const override;
    bool ReadFromString(const string &str) override;
};

class Move : public Task
{
public:
    enum MovementType
    {
        AlongLine,
        InPoint
    };

    enum MovementControlType
    {
        ByDepthSensor,
        BySonar
    };

private:
    inline static float maxX = 10000;
    inline static float minX = 0;

    inline static float maxY = 10000;
    inline static float minY = 0;

    float x = 5000;
    float y = 5000;

    float dr = 5;

    MovementType mType = InPoint;
    MovementControlType mcType = ByDepthSensor;

public:
    static ErrorState SetMaxMin(
        float maxX, float minX, float maxY, float minY);

    ErrorState SetX(float value);
    ErrorState SetY(float value);

    ErrorState SetMovementType(MovementType type);
    ErrorState SetMovementControlType(MovementControlType type);
    ErrorState SetPrecision(float value);

    static void GetMaxMinX(float &max, float &min);
    static void GetMaxMinY(float &max, float &min);

    void GetXY(float &x, float &y);

    MovementType GetMovementType();
    MovementControlType GetMovementControlType();
    float GetPrecision();

private:
    inline static const string headerStr = "Движение";

    inline static const string controlStr = "тип контроля погружения";

    inline static const string byDepthStr = "по глубине";
    inline static const string bySonarStr = "по отстоянию";

    inline static const string movementStr = "тип выхода";

    inline static const string inPointStr = "в точку";
    inline static const string alongLineStr = "вдоль линии";

    inline static const string pointStr = "координаты точки";
    inline static const string precisStr = "точность выхода";

public:
    static string GetHeader();

    const Move *Pointer() const override;
    TaskType Type() const override;
    string WriteToString() const override;
    bool ReadFromString(const string &str) override;
};

class Return : public Task
{
private:
    inline static const string headerStr = "Возвращение";

public:
    static string GetHeader();

    const Return *Pointer() const override;
    TaskType Type() const override;
    string WriteToString() const override;
    bool ReadFromString(const string &str) override;
};

#endif