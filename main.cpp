#include "matrix.h"
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <QStringList>

#define SIZE 6

using namespace std;

//Метод рекурсионого решения задачи
bool recurse(Matrix &m, int x, int y, int deph)
{
  //Если вышли за поле
  if(x < 0 || y < 0 || x >= m.size() || y >= m.size())
    return false;

  bool flagIsNotDelete = false;
  //Если клетка не пустая
  if(*m.take(x,y) > 0)
  {
    flagIsNotDelete = true;
    if(*m.take(x,y) != deph)
      return false;
  }
  //Если это последний элемент
  if(deph == m.size() * m.size())
  {
    *m.take(x,y) = deph;
    return true;
  }

  //Заполняем клетку
  *m.take(x,y) = deph;

  //Рекурсивно идем далее
  if(recurse(m,x+1,y,deph + 1))
    return true;
  if(recurse(m,x-1,y,deph + 1))
    return true;
  if(recurse(m,x,y+1,deph + 1))
    return true;
  if(recurse(m,x,y-1,deph + 1))
    return true;

  //Если все безуспешно
  if(!flagIsNotDelete)
    *m.take(x,y) = 0;
  return false;
}

//Метод печати матрицы
void printMatrix(Matrix &m)
{
  for (int x(0); x < m.size(); x++)
  {
    cout << "-|";
    for (int y(0); y < m.size(); y++)
    {
      if(*m.take(x,y) < 10)
        cout << "  " << *m.take(x,y) << " |";
      else
        cout << " " << *m.take(x,y) << " |";
    }
    cout << endl;
    for(int line(0); line < m.size(); line++) cout << "------";
    cout << endl;
  }
  cout << endl << endl;
}

//Метод чтения первичных элементов из файла
bool readListFromFile(Matrix &m)
{
  ifstream startDate("Start.txt");
  string line;
  if(startDate.is_open())
  {
    cout << "File open, loading" << endl;
    while(getline(startDate,line))
    {
      QString str;
      str = str.fromStdString(line);
      QStringList list = str.split(',');
      if(list.size() < 3 || list.size() > 3)
      {
          cout << "Problem with the number of items in a row." << endl;
          return false;
      }
      bool ok = true;
      *m.take(list[0].toInt(&ok) - 1,list[1].toInt(&ok) - 1) = list[2].toInt(&ok);
      if(!ok)
      {
          cout << "Probltm with the data." << endl;
          return false;
      }
    }
    startDate.close();
  }
  else
  {
    cout << "Problem with file" << endl;
  }
  return true;
}

int main(int argc, char *argv[])
{
  Matrix m(SIZE);
  for (int x(0); x < m.size(); x++)
    for (int y(0); y < m.size(); y++)
      *m.take(x,y) = 0;
  //printMatrix(m);
  if(!readListFromFile(m))
      return 1;
  printMatrix(m);
  for (int x(0); x < SIZE;x++)
  {
    for(int y(0); y < SIZE; y++)
    {
      if(*m.take(x,y) == 0 || *m.take(x,y) == 1)
          recurse(m,x,y,1);
    }
  }
  cout<<"------RESULT--------"<<endl;
  printMatrix(m);
  return 0;
}
