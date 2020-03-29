#ifndef GET_H
#define GET_H


class Get
{
private:
    int intVal;
    double dblVal;
public:
    Get();
    void GetInt(int*);
    void GetInt(int*, int, int);
    void GetIntMax(int*, int);
    void GetIntMin(int*, int);
    void GetDbl(double*);
    void GetDbl(double*, double, double);
    void GetDblMax(double*, double);
    void GetDblMin(double*, double);
    char* toString(int _number);
};

#endif // GET_H
