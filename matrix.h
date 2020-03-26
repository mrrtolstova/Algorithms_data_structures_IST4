#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

struct Size
{
  int width,height;
};

class Matrix
{
public:
  Matrix(int _size);
  int *take(int i, int j);
  void resize(int _m, int _n);
  int size();
  Matrix &operator=(const Matrix&);
private:
  std::vector<std::vector<int>> matrix;
  int m,n;
};

#endif // MATRIX_H
