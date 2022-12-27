// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование векторов

#include <iostream>
#include "tvector.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicVector<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с векторами" << endl;
  for (i = 0; i < 5; i++)
  {
    a[i] = i * 10;
    b[i] = (i + 1) * 11;
  }
  c = a + b;
  cout << "Vector a = " << endl << a << endl;
  cout << "Vector b = " << endl << b << endl;
  cout << "Vector c = a + b" << endl << c << endl;
}
//---------------------------------------------------------------------------