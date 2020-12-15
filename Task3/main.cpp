#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "Task.h"
#include "Mission.h"

using namespace std;

bool OpenExistingMission();
bool CreateNewMission();
bool SaveMissionToFile();

bool ConfigureMission();

bool CreateTask();
//Да будет костылик
bool CreateDive(Task *&task, bool lift = false);
bool CreateLift(Task *&task);
bool CreateMove(Task *&task);
bool CreateReturn(Task *&task);

bool OpenTask();
bool SwapTasks();

//Глобальные переменные зло
//А кто сказал, что я добрый...
Mission mission;
string fileName = "Mission.txt";

int main(int, char **)
{
    //Требуемые проверки в сам класс я добавли
    //Но не добавлял полную проверку корректности ввода
    //Можно было бы легко сделать помещая все в string

    //Также большое количество повторяющихся мест можно было вынести
    //в отдельные методы, которые, например принимает на вход строку
    //заголовка и список возможных вариантов, а на выходе дают
    //порядковый номер

    //Запрос на выход или сохранение тоже можно было бы отделить

    //Круто было бы вопсользоваться паттерном конечных автоматов
    //Но я уже фантазирую на случай, если будет время

    //Не знаю писал ли я это, но во многих местах проверки излишни
    //Или же некоторые if не будут достигнуты и т.п.
    //Однако, я сохранял структуру, чтобы не допустить ошибок

    cout << "Добрый день! Вас приветствует планировщик миссий\n";

    while (true)
    {
        cout << "Список возможных команд:\n";
        cout << "n - создать новую миссию\n";
        cout << "o - открыть сохраненную миссию\n";
        cout << "s - сохранить в файл миссию\n";
        cout << "q - выйти из планировщика\n";
        cout << "Введите команду: ";

        bool correctAnswer;
        char answer;

        cin >> answer;
        correctAnswer = false;
        cin.clear();

        cout << endl;

        if (answer == 'q')
            break;

        if (answer == 'n')
        {
            correctAnswer = true;

            if (!CreateNewMission())
                continue;
        }

        if (answer == 'o')
        {
            correctAnswer = true;

            if (!OpenExistingMission())
                continue;
        }

        if (answer == 's')
        {
            correctAnswer = true;

            SaveMissionToFile();
            continue;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }

        if (!ConfigureMission())
            break;
    }

    while (true)
    {
        bool correctAnswer;
        char answer;

        cout << "Сохранить текущую миссию?\n";
        cout << "y - да\n";
        cout << "n - нет\n";

        cin >> answer;
        correctAnswer = false;
        cin.clear();

        cout << endl;

        if (answer == 'y')
        {
            correctAnswer = true;
            SaveMissionToFile();
            break;
        }

        if (answer == 'n')
        {
            correctAnswer = true;
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }

        cout << endl;
    }

    cout << "Планировка миссий завершена\n";
}

bool OpenExistingMission()
{
    ifstream fin;
    fin.open(fileName);

    if (!fin.is_open())
    {
        cout << "Не удалось открыть файл с миссией!\n\n";
        return false;
    }

    stringstream missionStr;
    missionStr << fin.rdbuf();

    fin.close();

    if (!mission.ReadFromString(missionStr.str()))
    {
        cout << "Не удалось прочитать миссию из файла!\n\n";
        return false;
    }

    cout << "Миссия успешно открыта!\n\n";

    return true;
}

bool CreateNewMission()
{
    string missionName = "";

    while (true)
    {
        cout << "Введите название миссии: ";
        cin >> missionName;
        cin.clear();

        if (mission.SetName(missionName))
        {
            cout << "Миссия создана успешно!\n\n";
            break;
        }

        cout << "\nНекорректное имя!\n\n";
        continue;
    }

    return true;
}

bool SaveMissionToFile()
{
    ofstream fout;
    fout.open(fileName, ios_base::trunc);

    if (!fout.is_open())
    {
        cout << "Не удалось записать миссию в файл!\n\n";
        return false;
    }

    if (!mission.Correctness())
    {

        bool correctAnswer;
        char answer;

        while (true)
        {
            cout << "Миссия некорректна, все равно сохранить?\n";
            cout << "y - да\n";
            cout << "n - нет\n";

            cin >> answer;
            correctAnswer = false;
            cin.clear();

            cout << endl;

            if (answer == 'y')
            {
                correctAnswer = true;
                break;
            }

            if (answer == 'n')
            {
                correctAnswer = true;
                return false;
            }

            if (!correctAnswer)
            {
                cout << "Некорректная команда!\n\n";
                continue;
            }

            cout << endl;
        }
    }

    fout << mission.WriteToString();
    fout.close();

    cout << "Миссия успешно сохранена!\n\n";

    return true;
}

bool ConfigureMission()
{
    bool correctAnswer;
    char answer;

    while (true)
    {
        cout << "Команды для взаимодействия с миссией:\n";
        cout << "b - завершить редактирование\n";
        cout << "a - добавить задачу\n";
        cout << "o - открыть задачу\n";
        cout << "s - переставить задачи\n";
        cout << "p - вывести список задач\n";
        cout << "f - вывести полную информацию\n";
        cout << "q - выйти из планировщика\n";
        cout << "Введите команду: ";

        cin >> answer;
        correctAnswer = false;
        cin.clear();

        cout << endl;

        if (answer == 'b')
        {
            correctAnswer = true;
            return true;
        }

        if (answer == 'a')
        {
            correctAnswer = true;

            if (!CreateTask())
                return false;
        }

        if (answer == 'o')
        {
            correctAnswer = true;

            if (!OpenTask())
                return false;
        }

        if (answer == 's')
        {
            correctAnswer = true;

            if (!SwapTasks())
                return false;
        }

        if (answer == 'p')
        {
            correctAnswer = true;
            cout << mission.TasksListToString();
        }

        if (answer == 'f')
        {
            correctAnswer = true;
            cout << mission.WriteToString();
        }

        if (answer == 'q')
        {
            correctAnswer = true;
            return false;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }

        cout << endl;
    }
}

bool CreateTask()
{
    bool correctAnswer;
    char answer;

    Task *task = nullptr;

    while (true)
    {
        cout << "Команды создания задачи:\n";
        cout << "b - завершить создание\n";
        cout << "1 - Погружение\n";
        cout << "2 - Всплытие\n";
        cout << "3 - Движение\n";
        cout << "4 - Возвращение\n";
        cout << "q - выйти из планировщика\n";
        cout << "Введите команду: ";

        cin >> answer;
        correctAnswer = false;
        cin.clear();

        cout << endl;

        if (answer == 'b')
        {
            correctAnswer = true;
            return true;
        }

        if (answer == '1')
        {
            correctAnswer = true;

            if (!CreateDive(task))
                return false;
        }

        if (answer == '2')
        {
            correctAnswer = true;

            if (!CreateLift(task))
                return false;
        }

        if (answer == '3')
        {
            correctAnswer = true;

            if (!CreateMove(task))
                return false;
        }

        if (answer == '4')
        {
            correctAnswer = true;

            if (!CreateReturn(task))
                return false;
        }

        if (answer == 'q')
        {
            correctAnswer = true;
            return false;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }

        mission.AddTask(task);
    }

    return true;
}

bool CreateDive(Task *&task, bool lift)
{
    float depth;

    bool correctAnswer = false;
    char answer;

    Dive *d = nullptr;

    if (!lift)
        d = new Dive();
    else
        d = new Lift();

    while (true)
    {
        cout << "Введите глубину: ";
        cin >> depth;
        cin.clear();

        cout << endl;

        if (d->SetDepth(depth) != Dive::OutOfBounds)
            break;

        float max, min;
        Dive::GetMaxMinDepth(max, min);

        cout << "Глубина вне диапазона: "
             << max << " - " << min << "\n";
    }

    while (true)
    {
        cout << "Выберите тип измерения:\n";
        cout << "1 - по датчику глубины\n";
        cout << "2 - по сонару\n";

        cin >> answer;
        cin.clear();

        if (answer == '1')
        {
            correctAnswer = true;
            d->SetMeasurementType(Dive::ByDepthSensor);
            break;
        }

        if (answer == '2')
        {
            correctAnswer = true;
            d->SetMeasurementType(Dive::BySonar);
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    correctAnswer = false;

    while (true)
    {
        cout << "Выберите тип погружения:\n";
        cout << "1 - вертикально\n";
        cout << "2 - по спирали\n";

        cin >> answer;
        cin.clear();

        if (answer == '1')
        {
            correctAnswer = true;
            d->SetDiveType(Dive::Vertical);
            break;
        }

        if (answer == '2')
        {
            correctAnswer = true;
            d->SetDiveType(Dive::Spirally);
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    task = d;

    return true;
}

bool CreateLift(Task *&task)
{
    return CreateDive(task, true);
}

bool CreateMove(Task *&task)
{
    float x, y, r;

    bool correctAnswer = false;
    char answer;

    Move *m = new Move();

    while (true)
    {
        cout << "Введите X: ";
        cin >> x;
        cin.clear();

        cout << endl;

        if (m->SetX(x) != Move::OutOfBounds)
            break;

        float max, min;
        Move::GetMaxMinX(max, min);

        cout << "X вне диапазона: "
             << max << " - " << min << "\n";
    }

    while (true)
    {
        cout << "Введите Y: ";
        cin >> y;
        cin.clear();

        cout << endl;

        if (m->SetY(y) != Move::OutOfBounds)
            break;

        float max, min;
        Move::GetMaxMinY(max, min);

        cout << "Y вне диапазона: "
             << max << " - " << min << "\n";
    }

    while (true)
    {
        cout << "Введите dr: ";
        cin >> r;
        cin.clear();

        cout << endl;

        if (m->SetPrecision(y) != Move::OutOfBounds)
            break;

        cout << "dr вне диапазона!";
    }

    while (true)
    {
        cout << "Выберите тип движения:\n";
        cout << "1 - выход в точку\n";
        cout << "2 - вдоль линии\n";

        cin >> answer;
        cin.clear();

        if (answer == '1')
        {
            correctAnswer = true;
            m->SetMovementType(Move::InPoint);
            break;
        }

        if (answer == '2')
        {
            correctAnswer = true;
            m->SetMovementType(Move::AlongLine);
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    correctAnswer = false;

    while (true)
    {
        cout << "Выберите тип контроля глубины:\n";
        cout << "1 - по датчику глубины\n";
        cout << "2 - по сонару\n";

        cin >> answer;
        cin.clear();

        if (answer == '1')
        {
            correctAnswer = true;
            m->SetMovementControlType(Move::ByDepthSensor);
            break;
        }

        if (answer == '2')
        {
            correctAnswer = true;
            m->SetMovementControlType(Move::BySonar);
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    task = m;

    return true;
}

bool CreateReturn(Task *&task)
{
    task = new Return();
    return true;
}

bool OpenTask()
{
    bool correctAnswer = false;
    int position;
    char answer;

    while (true)
    {
        cout << "-1 - завершить открытие\n";
        cout << "Введите номер задачи: ";
        cin >> position;
        cin.clear();

        cout << endl;

        if (position == -1)
        {
            correctAnswer = true;
            return true;
        }

        if (position < 0 || position > mission.Count() - 1)
        {
            cout << "Такого номера нет!\n\n";
            continue;
        }
        else
        {
            correctAnswer = true;
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    correctAnswer = false;
    Task *task = mission.GetTask(position);

    while (true)
    {
        cout << task->WriteToString();
        cout << endl;

        cout << "b - завершить создание\n";
        cout << "e - изменить задачу\n";
        cout << "d - удалить задачу\n";
        cout << "q - выйти из планировщика\n";
        cin >> answer;
        cin.clear();

        cout << endl;

        if (answer == 'b')
        {
            correctAnswer = true;
            return true;
        }

        if (answer == 'e')
        {
            correctAnswer == true;

            switch (task->Type())
            {
            case Task::DiveTask:
                CreateDive(task);
                break;

            case Task::LiftTask:
                CreateLift(task);
                break;

            case Task::MoveTask:
                CreateMove(task);
                break;

            case Task::ReturnTask:
                CreateReturn(task);
                break;

            default:
                break;
            }

            mission.RemoveTask(position);
            mission.AddTask(task, position);
        }

        if (answer == 'd')
        {
            correctAnswer = true;
            mission.RemoveTask(position);
            break;
        }

        if (answer == 'q')
        {
            correctAnswer = true;
            return false;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    return true;
}

bool SwapTasks()
{
    bool correctAnswer = false;
    int position1, position2;

    while (true)
    {
        cout << "-1 - завершить смену позиций\n";
        cout << "Введите номер 1 задачи: ";
        cin >> position1;
        cin.clear();

        cout << endl;

        if (position1 == -1)
        {
            correctAnswer = true;
            return true;
        }

        if (position1 < 0 || position1 > mission.Count() - 1)
        {
            cout << "Такого номера нет!\n\n";
            continue;
        }
        else
        {
            correctAnswer = true;
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    while (true)
    {

        cout << endl;

        cout << "-1 - завершить смену позиций\n";
        cout << "Введите номер 2 задачи: ";
        cin >> position2;
        cin.clear();

        cout << endl;

        if (position2 == -1)
        {
            correctAnswer = true;
            return true;
        }

        if (position2 < 0 || position2 > mission.Count() - 1)
        {
            cout << "Такого номера нет!\n\n";
            continue;
        }
        else
        {
            correctAnswer = true;
            break;
        }

        if (!correctAnswer)
        {
            cout << "Некорректная команда!\n\n";
            continue;
        }
    }

    mission.SwapTasks(position1, position2);

    return true;
}