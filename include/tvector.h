// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicVector_H__
#define __TDynamicVector_H__

#include <iostream>

using namespace std;

const size_t MAX_VECTOR_SIZE = 100000000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  //TDynamicVector(size_t size = 1);
  TDynamicVector(size_t size = 1, const T& val = T());
  TDynamicVector(const T* arr, size_t s);
  TDynamicVector(const TDynamicVector& v);
  TDynamicVector(TDynamicVector&& v) noexcept;
  ~TDynamicVector();
  TDynamicVector& operator=(const TDynamicVector& v);
  TDynamicVector& operator=(TDynamicVector&& v) noexcept;

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind);
  const T& operator[](size_t ind) const;
  // индексация с контролем
  T& at(size_t ind);
  const T& at(size_t ind) const;

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept;
  bool operator!=(const TDynamicVector& v) const noexcept;

  // скалярные операции
  TDynamicVector operator+(const T& val);
  TDynamicVector operator-(const T& val);
  TDynamicVector operator*(const T& val);
  TDynamicVector operator/(const T& val);
  TDynamicVector operator-(void);

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v);
  TDynamicVector operator-(const TDynamicVector& v);
  T operator*(const TDynamicVector& v);

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      //ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
      ostr << v.pMem[i] << '\t'; // требуется оператор<< для типа T
    return ostr;
  }
};

//template<typename T>
//inline TDynamicVector<T>::TDynamicVector(size_t size) : sz(size)
//{
//  if (sz == 0)
//    throw out_of_range("Vector size should be greater than zero");
//  if (sz > MAX_VECTOR_SIZE)
//    throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
//  pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
//}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(size_t size, const T& val) : sz(size)
{
  if (sz == 0)
    throw out_of_range("Size should be greater than zero");
  if (sz > MAX_VECTOR_SIZE)
    throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
  pMem = new T[sz];
  for (size_t i = 0; i < sz; i++)
    pMem[i] = val;
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(const T* arr, size_t s) : sz(s)
{
  assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
  if (sz > MAX_VECTOR_SIZE)
    throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
  pMem = new T[sz];
  std::copy(arr, arr + sz, pMem);
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(const TDynamicVector& v)
{
  if (v.pMem == nullptr)
  {
    sz = 0;
    pMem = nullptr;
  }
  else
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector&& v) noexcept
{
  pMem = nullptr;
  swap(*this, v);
}

template<typename T>
inline TDynamicVector<T>::~TDynamicVector()
{
  delete[] pMem;
  sz = 0;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector& v)
{
  if (this == &v)
    return *this;
  if (sz != v.sz)
  {
    T* tmp = new T[v.sz];
    delete[] pMem;
    sz = v.sz;
    pMem = tmp;
  }
  std::copy(v.pMem, v.pMem + sz, pMem);
  return *this;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector&& v) noexcept
{
  swap(*this, v);
  v.pMem = nullptr;
  return *this;
}

template<typename T>
inline T& TDynamicVector<T>::operator[](size_t ind)
{
  return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::operator[](size_t ind) const
{
  return pMem[ind];
}

template<typename T>
inline T& TDynamicVector<T>::at(size_t ind)
{
  if (pMem == nullptr) throw "pMem is nullptr";
  if (ind >= sz) throw out_of_range("index is out of range");
  return this->operator[](ind);
}

template<typename T>
inline const T& TDynamicVector<T>::at(size_t ind) const
{
  if (pMem == nullptr) throw "pMem is nullptr";
  if (ind >= sz) throw out_of_range("index is out of range");
  return this->operator[](ind);
}

template<typename T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector& v) const noexcept
{
  if (v.sz != sz)
    return false;
  for (size_t i = 0; i < sz; i++)
    if (this->operator[](i) != v[i])
      return false;
  return true;
}

template<typename T>
inline bool TDynamicVector<T>::operator!=(const TDynamicVector& v) const noexcept
{
  return !(this->operator==(v));
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const T& val)
{
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) + val;
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const T& val)
{
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) - val;
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(const T& val)
{
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) * val;
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator/(const T& val)
{
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) / val;
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector& v)
{
  if (sz != v.sz) throw "Sizes are not equal";
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) + v[i];
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector& v)
{
  if (sz != v.sz) throw "Sizes are not equal";
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = this->operator[](i) - v[i];
  return tmp;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-()
{
  TDynamicVector<T> tmp(sz);
  for (size_t i = 0; i < sz; i++)
    tmp[i] = -(this->operator[](i));
  return tmp;
}

template<typename T>
inline T TDynamicVector<T>::operator*(const TDynamicVector& v)
{
  if (sz != v.sz) throw "Sizes are not equal";
  T tmp = T();
  for (size_t i = 0; i < sz; i++)
    tmp = tmp + this->operator[](i) * v[i];
  return tmp;
}

#endif
