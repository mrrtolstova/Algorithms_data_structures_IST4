#include "get.h"
#include <iostream>

using namespace std;

Get::Get()
{
    intVal = 0;
    dblVal = 0;
}

void Get::GetInt(int *tmpVal)
{
    cin >> *tmpVal;
    //Если не верно
    if (!(cin))
    {
        //Подготавливаем поток к повторному вводу
        cin.clear();
        cin.sync();
        cin.ignore();
        *tmpVal = - 1;
    }
    system("cls");
    cout << "Incorect, please repeat input: ";
}

void Get::GetInt(int *tmpVal, int min, int max)
{
    //Если мин больше меняем местами
    if(min > max)
    {
        max+=min;
        min = max - min;
        max = max - min;
    }
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = min - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal < min || *tmpVal > max);
    system("cls");
}

void Get::GetIntMax(int *tmpVal, int max)
{
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal > max);
    system("cls");
}

void Get::GetIntMin(int *tmpVal, int min)
{
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal < min);
    system("cls");
}

void Get::GetDbl(double *tmpVal)
{
    cin >> *tmpVal;
    //Если не верно
    if (!(cin))
    {
        //Подготавливаем поток к повторному вводу
        cin.clear();
        cin.sync();
        cin.ignore();
        *tmpVal = - 1.0;
    }
    system("cls");
}

void Get::GetDbl(double *tmpVal, double min, double max)
{
    //Если мин больше меняем местами
    if(min > max)
    {
        max+=min;
        min = max - min;
        max = max - min;
    }
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = min - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal < min || *tmpVal > max);
    system("cls");
}

void Get::GetDblMax(double *tmpVal, double max)
{
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal > max);
    system("cls");
}

void Get::GetDblMin(double *tmpVal, double min)
{
    //Вводи значение пока не будет верно
    do{
        //Вводим значение
        cin >> *tmpVal;
        //Если не верно
        if (!(cin))
        {
            //Подготавливаем поток к повторному вводу
            cin.clear();
            cin.sync();
            cin.ignore();
            *tmpVal = - 1;
        }
        system("cls");
        cout << "Incorect, please repeat input: ";
    } while (*tmpVal < min);
    system("cls");
}

char* Get::toString(int _number) {
    int m = _number;
    int k = 0;
    char *result;
    while(m!=0) {
        k++;
        m = m/10;
    }
    result = new char[k+1];
    sprintf(result, "%d", _number);
    return result;
}
