#include <iostream>
#include <string>
#include "Header.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    cout << "Удаление ведущих нулей"<<endl;
    TestRemoveZeros();

    cout << "Сравнение чисел:" << endl;
    TestLessThanOrEqual();

    cout << "Вычитание чисел:" << endl;
    TestSubtract();

    cout << "Деление единицы на число:" << endl;
    TestOneDibBy();
}
