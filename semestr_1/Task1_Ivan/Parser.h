#ifndef Parser_H
#define Parser_H

// Структура данных, в которую будет записана посылка
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

// Перечисление, содержащее все заголовки данных
enum Headers : char
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

// Подпрограмма, осуществляющая конвертацию BE --> LE
void to_LE(char *bytes, int size)
{
    // Цикл простой перестановки байт
    char temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = bytes[i];
        bytes[i] = bytes[(size - 1) - i];
        bytes[(size - 1) - i] = temp;
    }
}

// Шаблонная подпрограмма, позволяющая осуществлять запись байт
// в поле произвольного типа
template <class T>
int bytes_to_field(T *field, char *bytes, int length)
{
    // Узнаем количество байт, требуемое конкретным типом
    int typeSize = sizeof(T);
    // Если требуется байт больше, чем их осталось в посылке, то выходим
    if (typeSize > length)
        return length;
    //Иначе осуществляем конвертацию
    to_LE(bytes, typeSize);
    // И записываем байты в поле структуры
    *field = *(T *)bytes;
    // Возвращаем количество записанных байт, чтобы
    // внешняя подпрограмма сдвинула указатель на байты посылки,
    // пропустив уже записанные байты
    return typeSize;
}

// Подпрограмма записи посылки в структуру данных
Data bytes_to_data(const char *bytes, int length)
{
    // Создаем структуру данных, в которую будет осуществляться запись посылки
    Data data;
    // Создаем временное хранилище байт, которое можно будет редактировать в процессе
    char t_bytes[length];
    // Записываем посылку в наше временное хранилище
    for (int i = 0; i < length; i++)
        t_bytes[i] = bytes[i];
    // В главном цикле осуществляется проход по всем байтам посылки
    for (int i = 0; i < length;)
    {
        // Проверяем какому заголовку соответствует текущий байт
        // Если заголовок распознан, то осуществляем запись последующих байт в поле структуры
        // Если заголовок не распознан, то переходим к следующему байту
        switch ((int)t_bytes[i++])
        {
        case kHeading:
            // Осуществляем запись данных в поле
            // и смещаем указатель на записанное количество байт
            i += bytes_to_field(&data.kHeading, t_bytes + i, length - i);
            continue;
        case kPitch:
            i += bytes_to_field(&data.kPitch, t_bytes + i, length - i);
            continue;
        case kRoll:
            i += bytes_to_field(&data.kRoll, t_bytes + i, length - i);
            continue;
        case kHeadingStatus:
            i += bytes_to_field(&data.kHeadingStatus, t_bytes + i, length - i);
            continue;
        case kQuaternion:
            i += bytes_to_field(&data.kQuaternion[0], t_bytes + i, length - i);
            i += bytes_to_field(&data.kQuaternion[1], t_bytes + i, length - i);
            i += bytes_to_field(&data.kQuaternion[2], t_bytes + i, length - i);
            i += bytes_to_field(&data.kQuaternion[3], t_bytes + i, length - i);
            continue;
        case kTemperature:
            i += bytes_to_field(&data.kTemperature, t_bytes + i, length - i);
            continue;
        case kDistortion:
            i += bytes_to_field(&data.kDistortion, t_bytes + i, length - i);
            continue;
        case kCalStatus:
            i += bytes_to_field(&data.kCalStatus, t_bytes + i, length - i);
            continue;
        case kAccelX:
            i += bytes_to_field(&data.kAccelX, t_bytes + i, length - i);
            continue;
        case kAccelY:
            i += bytes_to_field(&data.kAccelY, t_bytes + i, length - i);
            continue;
        case kAccelZ:
            i += bytes_to_field(&data.kAccelZ, t_bytes + i, length - i);
            continue;
        case kMagX:
            i += bytes_to_field(&data.kMagX, t_bytes + i, length - i);
            continue;
        case kMagY:
            i += bytes_to_field(&data.kMagY, t_bytes + i, length - i);
            continue;
        case kMagZ:
            i += bytes_to_field(&data.kMagZ, t_bytes + i, length - i);
            continue;
        case kGyroX:
            i += bytes_to_field(&data.kGyroX, t_bytes + i, length - i);
            continue;
        case kGyroY:
            i += bytes_to_field(&data.kGyroY, t_bytes + i, length - i);
            continue;
        case kGyroZ:
            i += bytes_to_field(&data.kGyroZ, t_bytes + i, length - i);
            continue;
        }
    }

    // Возвращаем полученную структуру
    return data;
}

// Подпрограмма осуществляет вывод данных структуры в консоль (в читаемом виде)
void Print(const Data& data)
{
    std::cout << "kHeading = " << data.kHeading << std::endl;
    std::cout << "kPitch = " << data.kPitch << std::endl;
    std::cout << "kRoll = " << data.kRoll << std::endl;
    std::cout << "kHeadingStatus = " << data.kHeadingStatus << std::endl;

    std::cout << "kQuaternion[0] = " << data.kQuaternion[0] << std::endl;
    std::cout << "kQuaternion[1] = " << data.kQuaternion[1] << std::endl;
    std::cout << "kQuaternion[2] = " << data.kQuaternion[2] << std::endl;
    std::cout << "kQuaternion[3] = " << data.kQuaternion[3] << std::endl;

    std::cout << "kTemperature = " << data.kTemperature << std::endl;
    std::cout << "kDistortion = " << data.kDistortion << std::endl;
    std::cout << "kCalStatus = " << data.kCalStatus << std::endl;
    std::cout << "kAccelX = " << data.kAccelX << std::endl;
    std::cout << "kAccelY = " << data.kAccelY << std::endl;
    std::cout << "kAccelZ = " << data.kAccelZ << std::endl;
    std::cout << "kMagX = " << data.kMagX << std::endl;
    std::cout << "kMagY = " << data.kMagY << std::endl;
    std::cout << "kMagZ = " << data.kMagZ << std::endl;
    std::cout << "kGyroX = " << data.kGyroX << std::endl;
    std::cout << "kGyroY = " << data.kGyroY << std::endl;
    std::cout << "kGyroZ = " << data.kGyroZ << std::endl;
}

#endif