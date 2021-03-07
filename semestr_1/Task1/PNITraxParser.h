#ifndef PNITraxParser_H
#define PNITraxParser_H

class PNITraxParser
{
public:
    struct Data
    {
        float kHeading = 0;
        float kPitch = 0;
        float kRoll = 0;

        char kHeadingStatus = 0;

        float kQuaternion[4] = {0};

        float kTemperature = 0;

        bool kDistortion = false;
        bool kCalStatus = false;

        float kAccelX = 0;
        float kAccelY = 0;
        float kAccelZ = 0;

        float kMagX = 0;
        float kMagY = 0;
        float kMagZ = 0;

        float kGyroX = 0;
        float kGyroY = 0;
        float kGyroZ = 0;
    };

private:
    enum DataType : char
    {
        kHeading = 5,
        kPitch = 24,
        kRoll = 25,
        kHeadingStatus = 79,
        kQuaternion = 77,
        kTemperature = 7,
        kDistortion = 8,
        kCalStatus = 9,
        kAccelX = 21,
        kAccelY = 22,
        kAccelZ = 23,
        kMagX = 27,
        kMagY = 28,
        kMagZ = 29,
        kGyroX = 74,
        kGyroY = 75,
        kGyroZ = 76
    };

    Data data;

public:
    void GetFromString(const char *str, int length);
    Data GetData();
    void SetData(const Data &data);
    void PrintData();

private:
    void ConvertToLE(char* bytes, int count);

    template<class T>
    int Fill(T* field, char* str, int);
};

#endif