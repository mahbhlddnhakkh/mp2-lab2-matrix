// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include "tvector.h"
#include <iostream>

using namespace std;

const size_t MAX_MATRIX_SIZE = 10000;


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1);

  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;

  void Transpose();
  TDynamicMatrix Cofactor(size_t i, size_t j) const;
  T Det() const;
  T Minor(size_t i, size_t j) const;
  TDynamicMatrix Invertible() const;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept;
  bool operator!=(const TDynamicMatrix& m) const noexcept;

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val);
  TDynamicMatrix operator/(const T& val);

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v);

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m);
  TDynamicMatrix operator-(const TDynamicMatrix& m);
  TDynamicMatrix operator*(const TDynamicMatrix& m);
  TDynamicMatrix operator/(const TDynamicMatrix& m);

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
    for (size_t i = 0; i < m.sz; i++)
      istr >> m.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
    for (size_t i = 0; i < m.sz; i++)
      ostr << m.pMem[i] << endl;
    return ostr;
  }
};

template<typename T>
inline TDynamicMatrix<T>::TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
{
  if (sz > MAX_MATRIX_SIZE)
    throw out_of_range("Matrix size should be less than MAX_MATRIX_SIZE");
  for (size_t i = 0; i < sz; i++)
    pMem[i] = TDynamicVector<T>(sz);
}

template<typename T>
inline void TDynamicMatrix<T>::Transpose()
{
  TDynamicMatrix<T> tmp(*this);
  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++)
      (this->operator[](i))[j] = tmp[j][i];
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::Cofactor(size_t i, size_t j) const
{
  (this->at(i)).at(j);
  if (sz == 1)
    throw "Can't have cofactor matrix from matrix with size 1";
  TDynamicMatrix<T> tmp(sz - 1);

  size_t tmp1 = 0, tmp2 = 0;
  for (size_t k = 0; k < sz - 1; k++)
  {
    if (k == i)
      tmp1 = 1;
    for (size_t l = 0; l < sz - 1; l++)
    {
      if (l == j)
        tmp2 = 1;
      tmp[k][l] = (this->operator[](k + tmp1))[l + tmp2];
    }
    tmp2 = 0;
  }
  return tmp;
}

template<typename T>
inline T TDynamicMatrix<T>::Det() const
{
  if (sz == 1)
    return (this->operator[](0))[0];
  else if (sz == 2)
    return ((this->operator[](0))[0] * (this->operator[](1))[1] - (this->operator[](1))[0] * (this->operator[](0))[1]);
  else
  {
    T d = 0;
    bool posSign = true;
    for (size_t k = 0; k < sz; k++)
    {
      T temp = (this->operator[](k))[0] * this->Minor(k, 0);
      if (posSign)
        d = d + temp;
      else
        d = d - temp;
      posSign = !posSign;
    }
    return d;
  }
}

template<typename T>
inline T TDynamicMatrix<T>::Minor(size_t i, size_t j) const
{
  TDynamicMatrix<T> tmp = this->Cofactor(i, j);
  return tmp.Det();
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::Invertible() const
{
  T d = this->Det();
  if (d == 0)
    throw "Can't have inverible matrix with det = 0.";
  if (sz == 1)
  {
    TDynamicMatrix<T> tmp(*this);
    return (tmp / d);
  }
  TDynamicMatrix<T> tmp(sz);
  bool posSign = true;
  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++)
    {
      tmp[i][j] = this->Minor(i, j);
      if (!posSign)
        tmp[i][j] = -tmp[i][j];
      posSign = !posSign;
    }
  tmp.Transpose();
  return (tmp / d);
}

template<typename T>
inline bool TDynamicMatrix<T>::operator==(const TDynamicMatrix& m) const noexcept
{
  return this->TDynamicVector<TDynamicVector<T>>::operator==(m);
}

template<typename T>
inline bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix& m) const noexcept
{
  return !(this->operator==(m));
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val)
{
  TDynamicMatrix<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) * val;
  return tmp;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator/(const T& val)
{
  TDynamicMatrix<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) / val;
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v)
{
  if (sz != v.size()) throw "Sizes are not equal";
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) * v;
  return tmp;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix& m)
{
  if (sz != m.sz) throw "Sizes are not equal";
  TDynamicMatrix<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) + m[i];
  return tmp;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix& m)
{
  if (sz != m.sz) throw "Sizes are not equal";
  TDynamicMatrix<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) - m[i];
  return tmp;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix& m)
{
  if (sz != m.sz) throw "Sizes are not equal";
  TDynamicMatrix<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < sz; j++)
      for (size_t k = 0; k < sz; k++)
        tmp[i][j] = tmp[i][j] + (this->operator[](i))[k] * m[k][j];
  return tmp;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator/(const TDynamicMatrix& m)
{
  if (sz != m.sz) throw "Sizes are not equal";
  TDynamicMatrix<T> tmp = m.Invertible();
  return ((*this) * tmp);
}

#endif
