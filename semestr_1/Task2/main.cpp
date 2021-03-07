#include <iostream>
#include "LinkedList.h"

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    LinkedList<double> list;

    list.PushBack(4);
    list.PushBack(14);
    list.PushBack(5);
    list.PushBack(6);
    list.PushBack(1);
    list.PushBack(22);
    list.PushBack(7);

    for (auto iter = list.Begin(); iter != list.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;
    list.Sort();

    for (auto iter = list.Begin(); iter != list.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    LinkedList<int> emptyList;
    emptyList.PushBack(4);
    emptyList.PushBack(14);

    emptyList.Sort();

    for (auto iter = emptyList.Begin(); iter != emptyList.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    LinkedList<float> list2;
    list2.PushBack(6);
    list2.PushBack(4);
    list2.PushBack(14);

    list2.Sort();

    for (auto iter = list2.Begin(); iter != list2.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    LinkedList<float> list3;
    list3.PushBack(4);
    list3.PushBack(6);
    list3.PushBack(14);

    list3.Sort();

    for (auto iter = list3.Begin(); iter != list3.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    LinkedList<float> list4;
    list4.PushBack(14);
    list4.PushBack(6);
    list4.PushBack(4);

    list4.Swap(0, 2);

    for (auto iter = list4.Begin(); iter != list4.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    list4.Sort();

    for (auto iter = list4.Begin(); iter != list4.End(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl
              << std::endl;

    LinkedList<float> list5;
    list5.PushBack(14);
    list5.PushBack(8);
    list5.PushBack(4);
    list5.PushBack(6);
    list5.PushBack(4);
    list5.PushBack(6);

    list5.Sort();

    for (auto iter = list5.Begin(); iter != list5.End(); iter++)
        std::cout << *iter << std::endl;
}
