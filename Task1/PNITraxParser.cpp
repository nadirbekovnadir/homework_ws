#include "PNITraxParser.h"
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;


void PNITraxParser::GetFromString(const char *bytes, int length)
{
    //Привычка не использовать динамическую память
    char tBytes[length];
    for (int i = 0; i < length; i++)
        tBytes[i] = bytes[i];

    //Не спрашивайте...
    for (int i = 0; i < length;)
    {
        int typeSize = 0;

        switch ((int)tBytes[i])
        {
        case kHeading:
            i++;
            i += Fill(&data.kHeading,
                      tBytes + i, length - i);
            continue;

        case kPitch:
            i++;
            i += Fill(&data.kPitch,
                      tBytes + i, length - i);
            continue;

        case kRoll:
            i++;
            i += Fill(&data.kRoll,
                      tBytes + i, length - i);
            continue;

        case kHeadingStatus:
            i++;
            i += Fill(&data.kHeadingStatus,
                      tBytes + i, length - i);
            continue;

        case kQuaternion:
            i++;
            i += Fill(&data.kQuaternion[0],
                      tBytes + i, length - i);
            i += Fill(&data.kQuaternion[1],
                      tBytes + i, length - i);
            i += Fill(&data.kQuaternion[2],
                      tBytes + i, length - i);
            i += Fill(&data.kQuaternion[3],
                      tBytes + i, length - i);
            continue;

        case kTemperature:
            i++;
            i += Fill(&data.kTemperature,
                      tBytes + i, length - i);
            continue;

        case kDistortion:
            i++;
            i += Fill(&data.kDistortion,
                      tBytes + i, length - i);
            continue;

        case kCalStatus:
            i++;
            i += Fill(&data.kCalStatus,
                      tBytes + i, length - i);
            continue;

        case kAccelX:
            i++;
            i += Fill(&data.kAccelX,
                      tBytes + i, length - i);
            continue;

        case kAccelY:
            i++;
            i += Fill(&data.kAccelY,
                      tBytes + i, length - i);
            continue;

        case kAccelZ:
            i++;
            i += Fill(&data.kAccelZ,
                      tBytes + i, length - i);
            continue;

        case kMagX:
            i++;
            i += Fill(&data.kMagX,
                      tBytes + i, length - i);
            continue;

        case kMagY:
            i++;
            i += Fill(&data.kMagY,
                      tBytes + i, length - i);
            continue;

        case kMagZ:
            i++;
            i += Fill(&data.kMagZ,
                      tBytes + i, length - i);
            continue;

        case kGyroX:
            i++;
            i += Fill(&data.kGyroX,
                      tBytes + i, length - i);
            continue;

        case kGyroY:
            i++;
            i += Fill(&data.kGyroY,
                      tBytes + i, length - i);
            continue;

        case kGyroZ:
            i++;
            i += Fill(&data.kGyroZ,
                      tBytes + i, length - i);
            continue;

        default:
            i++;
            continue;
        }
    }
}

PNITraxParser::Data PNITraxParser::GetData()
{
    return data;
}

void PNITraxParser::SetData(const Data &data)
{
    this->data = data;
}

void PNITraxParser::PrintData()
{
    cout << "kHeading = " << data.kHeading << endl;
    cout << "kPitch = " << data.kPitch << endl;
    cout << "kRoll = " << data.kRoll << endl;

    cout << "kHeadingStatus = " << data.kHeadingStatus << endl;

    cout << "kHeading = " << data.kHeading << endl;

    cout << "kTemperature = " << data.kTemperature << endl;

    cout << "kDistortion = " << data.kDistortion << endl;
    cout << "kCalStatus = " << data.kCalStatus << endl;

    cout << "kAccelX = " << data.kAccelX << endl;
    cout << "kAccelY = " << data.kAccelY << endl;
    cout << "kAccelZ = " << data.kAccelZ << endl;

    cout << "kMagX = " << data.kMagX << endl;
    cout << "kMagY = " << data.kMagY << endl;
    cout << "kMagZ = " << data.kMagZ << endl;

    cout << "kGyroX = " << data.kGyroX << endl;
    cout << "kGyroY = " << data.kGyroY << endl;
    cout << "kGyroZ = " << data.kGyroZ << endl;


}

void PNITraxParser::ConvertToLE(char *bytes, int count)
{

    char temp;

    for (int i = 0; i < count / 2; i++)
    {
        temp = bytes[i];
        bytes[i] = bytes[(count - 1) - i];
        bytes[(count - 1) - i] = temp;
    }
}

template <class T>
int PNITraxParser::Fill(T *field, char *bytes, int length)
{
    int typeSize = sizeof(T);
    if (typeSize > length)
        return length;

    ConvertToLE(bytes, typeSize);
    *field = *(T *)bytes;

    return typeSize;
}