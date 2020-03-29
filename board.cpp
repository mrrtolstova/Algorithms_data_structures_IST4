#include <iostream>
#include "board.h"
#include "get.h"

//Конструктор, принимает размер поля
//Необходим для выделения памяти и инициализаций
Board::Board()
{
    //Инициализируем размер поля
    mSize_of_board = 3;
    //Выделяем память под массив значений
    mData = new int[mSize_of_board * 2];
    //Присваеваем первое значение счетчика
    count_of_val = -1;
    //Выделяем память под координаты (С избытком, что бы избежать выхода за массив)
    pos_of_val_X = new int[mSize_of_board * 2];
    pos_of_val_Y = new int[mSize_of_board * 2];
    //Собираем поле и выделяем под него память
    mBoard = new Cell* [mSize_of_board];
    {
        for(int i(0); i < mSize_of_board; i++)
        {
            mBoard[i] = new Cell [mSize_of_board];
        }
    }
    //Инициализируем поле
    for (int i(0); i < mSize_of_board; i++)
    {
        for(int j(0); j < mSize_of_board; j++)
        {
            mBoard[i][j].SetVal(0);
            mBoard[i][j].SetNumOfVal(-1);
        }
    }
}

//Диструктор, служит для очистки памяти
Board::~Board()
{
    for(int i(0); i < mSize_of_board; i++)
    {
        delete mBoard[i];
    }
    delete mBoard;
    delete pos_of_val_X;
    delete pos_of_val_Y;
    delete mData;
}

//Метод печати поля
//Выводит поле в консоль
void Board::PrintBoard()
{
   std::cout << "|\\";
   for (int i = 0; i < mSize_of_board; i++)
   {
       if(i < 9)
       {
           std::cout << "|- ";
       }
       else
       {
           std::cout << "|-";
       }
       std::cout <<i + 1<< " -|";
   }
   std::cout << " " << std::endl;
   for (int i = 0; i < mSize_of_board; i++)
   {
       if(i < 9)
       {
           std::cout << i + 1;
           std::cout << " ";
       }
       else
       {
           std::cout << i + 1;
       }
               for (int j = 0; j < mSize_of_board; j++)
               {
                   if(mBoard[i][j].GetVal() < 9)
                   {
                       std::cout << "|- ";
                   }
                   else
                   {
                       std::cout << "|-";
                   }
                   std::cout << mBoard[i][j].GetVal() << " -|";
               }
           std::cout << " " << std::endl;
   }
}

//Метод очистки
//Выполняет откат в случае ошибки расположения фигуры в Метода Solution
void Board::Clear()
{
                                                                                    // Если была ошибка в подборе расположения то очищаем
    for (int i(0); i < mSize_of_board; i++)                                         // поле от последней фигуры и спускаем флаг.
    {                                                                               // (Пересечение с другой фигурой)
        for(int j(0); j < mSize_of_board; j++)                                      //------------------------------------------
        {
            if(mBoard[i][j].GetVal() == 0 && mBoard[i][j].GetNumOfVal() == count_of_val)
            {
                mBoard[i][j].SetNumOfVal(-1);
            }
        }
    }
}

//Метод решения
// рекурсивно перебирает все возможные варианты решения головоломки
bool Board::Solution()
{
    //Флаг для контроля ошибок
    int flag_of_error = 0;
    for (int length(1); length < mSize_of_board + 1; length++)                                              //------------------------------------------
    {                                                                                                       // Подбор длины и ширины для фигуры
        for (int width(1); width < mSize_of_board + 1; width++)                                             // заданной площади
        {                                                                                                   //
            if(length * width == mBoard[pos_of_val_X[count_of_val]][pos_of_val_Y[count_of_val]].GetVal())   //------------------------------------------
            {
                for(int prm_l(1); prm_l < length + 1; prm_l++)                                              //------------------------------------------
                {                                                                                           // Подбор местоположения фигуры
                    for(int prm_w(1); prm_w < width + 1; prm_w++)                                           //------------------------------------------
                    {
                        //Подбираем "параметры" для вычисления клеток принадлежащих фигуре
                        //Что в последствии покажет ее местоположение
                            int temp_l = length;
                            int temp_w = width;
                            temp_l -= prm_l;
                            temp_w -= prm_w;
                            for(int k(0); k < length; k++)
                            {
                                temp_w = width - prm_w;
                                for(int p(0); p < width; p++)
                                {
                                    //Вычесляем каждую координату для нахождения клетки фигуры
                                    int temp_x = pos_of_val_X[count_of_val] - temp_l;
                                    int temp_y = pos_of_val_Y[count_of_val] - temp_w;
                                    //Проверка выхода за пределы массива
                                    if(temp_x > -1 && temp_y > -1 && (temp_x >= mSize_of_board || temp_y >= mSize_of_board))
                                    {
                                        flag_of_error = 1;
                                    }
                                    //Если клетка не пренадлежит другой фигуре, то отправляем значение блока в клетку
                                    else if(temp_x > -1 && temp_y > -1 && (mBoard[temp_x][temp_y].GetNumOfVal() == -1 || mBoard[temp_x][temp_y].GetVal() == mData[count_of_val]))
                                    {
                                        mBoard[temp_x][temp_y].SetNumOfVal(count_of_val);
                                    }
                                    //В любом другом случае - ошибка
                                    else
                                    {
                                        flag_of_error = 1;
                                    }
                                    temp_w--;
                                }
                                temp_l--;
                            }
                            //Если фигура расположилась на поле без ошибок
                            if(flag_of_error == 0)
                            {
                                //Если ещё есть фигуры
                                if(count_of_val > 0)
                                {
                                    //Находим их местоположение
                                    count_of_val--;
                                    if(Solution())
                                    {
                                        //Если нашли, возвращаем true
                                        count_of_val++;
                                        return true;
                                    }
                                    else
                                    {
                                        //Если не нашли, подбираем другое положение для нашей фигуры
                                        flag_of_error = 1;
                                    }
                                }
                                else
                                {
                                    //Если фигура последняя, возвращаем true
                                    count_of_val++;
                                    return true;
                                }
                            }
                            //Откат в случае ошибок
                            if(flag_of_error == 1)
                            {
                                Clear();
                                flag_of_error = 0;
                            }
                    }
                }
            }
        }
    }
    //Если решение не было найдено
    count_of_val++;
    return false;
}

//Метод печати ответа на головоломку
//Считывает принадлежность к блоку, и ставит соответствующее число в клетку
void Board::Answer()
{
    if(Solution())
    {
        for (int i(0); i < mSize_of_board; i++)
        {
            for(int j(0); j < mSize_of_board; j++)
            {
                mBoard[i][j].SetVal(mData[mBoard[i][j].GetNumOfVal()]);
            }
        }
    }
}

//Метод ввода данных
//Принимает задачу от пользователя
void Board::Input()
{
    //Временная переменная для передачи значения клетки
    int temp_val = 0;
    //До тех пор пока пользователь не отменил ввод
    while(temp_val == 0)
    {
        //Счетчик кол-ва фигур ++
        count_of_val++;
        //Создаем объект для коректного ввода
        Get get;
        //Создаем временные переменные для координат
        int temp_X,temp_Y;
        //Принимаем данные
        std::cout << "Input value of cell: ";
        get.GetIntMin(&temp_val, 1);
        std::cout << "Input value of raw: ";
        get.GetInt(&temp_X, 1, mSize_of_board);
        temp_X--;
        std::cout << "Input value of colomn: ";
        get.GetInt(&temp_Y, 1, mSize_of_board);
        temp_Y--;
        //Отправляем данные по назначению
        for (int i(0); i < mSize_of_board; i++)
        {
            for(int j(0); j < mSize_of_board; j++)
            {
                if(temp_X == i && temp_Y == j)
                {
                    if(mBoard[i][j].GetVal() == 0)
                    {
                        //Забиваем позицию элемента в память класса
                        pos_of_val_X[count_of_val] = i;
                        pos_of_val_Y[count_of_val] = j;
                        //А так же значение
                        mData[count_of_val] = temp_val;
                        //Проставляем номер блока клетки
                        mBoard[i][j].SetNumOfVal(count_of_val);
                    }
                    //Проставляем значение клетки
                    mBoard[i][j].SetVal(temp_val);
                }
            }
        }
        //Печатаем поле
        PrintBoard();
        //Спрашиваем есть ли ещё данные
        std::cout << "New value accept!\n For new value input \"0\"" << std::endl;
        get.GetInt(&temp_val);
    }
}
