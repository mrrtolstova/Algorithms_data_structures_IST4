#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell();
    //Метод получения значения клетки
    int GetVal() { return mVal; }
    //Метод установки значения клетки
    void SetVal(int val) { mVal = val; }
    //Метод получения номера блока
    int GetNumOfVal() { return num_of_mVal; }
    //Метод установки номера блока
    void SetNumOfVal(int val) { num_of_mVal = val; }
private:
    int mVal;
    int num_of_mVal;
};

#endif // CELL_H
