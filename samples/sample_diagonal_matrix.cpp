// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "TDTriangleMatrix.h"
#include "TUTriangleMatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDTriangleMatrix<int> a1(5), b1(5), c1(5);
  TUTriangleMatrix<int> a2(5), b2(5), c2(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с треугольными матрицами" << endl;
  for (i = 0; i < 5; i++)
    for (j = 0; j < i; j++)
    {
      a1[i][j] = i * 10 + j;
      b1[i][j] = (i * 10 + j) * 100;
    }
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++)
    {
      a2(i, j) = i * 10 + j;
      b2(i, j) = (i * 10 + j) * 100;
    }

  c1 = a1 + b1;
  c2 = a2 + b2;
  cout << "Matrix a1 = " << endl << a1 << endl;
  cout << "Matrix b1 = " << endl << b1 << endl;
  cout << "Matrix c1 = a1 + b1" << endl << c1 << endl;

  cout << "Matrix a2 = " << endl << a2 << endl;
  cout << "Matrix b2 = " << endl << b2 << endl;
  cout << "Matrix c2 = a2 + b2" << endl << c2 << endl;
}
//---------------------------------------------------------------------------