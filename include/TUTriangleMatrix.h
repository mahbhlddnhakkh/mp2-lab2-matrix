// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// 
//
//

#ifndef __TUTriangleMatrix_H__
#define __TUTriangleMatrix_H__

#include "tmatrix.h"
#include <iostream>

using namespace std;

template<typename T>
class TUTriangleMatrix : private TDynamicVector<TDynamicVector<T>>
{
protected:
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;

public:
	TUTriangleMatrix(size_t s = 2, const T& val = T());

	using TDynamicVector<TDynamicVector<T>>::size;
	//using TDynamicVector<TDynamicVector<T>>::operator[];
	//using TDynamicVector<TDynamicVector<T>>::at;
	T& operator()(size_t i, size_t j);
	T& at(size_t i, size_t j);
	const T& operator()(size_t i, size_t j) const;
	const T& at(size_t i, size_t j) const;

	// сравнение
	bool operator==(const TUTriangleMatrix& m) const noexcept;
	bool operator!=(const TUTriangleMatrix& m) const noexcept;

	// скалярные операции
	TUTriangleMatrix operator*(const T& val);
	TUTriangleMatrix operator/(const T& val);
	TUTriangleMatrix operator-(void);

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v);

	// матричные операции
	TUTriangleMatrix operator+(const TUTriangleMatrix& m);
	TUTriangleMatrix operator-(const TUTriangleMatrix& m);
	TUTriangleMatrix operator*(const TUTriangleMatrix& m);

	friend istream& operator>>(istream& istr, TUTriangleMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			istr >> m.pMem[i];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TUTriangleMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
		{
			for (size_t j = 0; j < i; j++)
				// ostr << '0' << ' ';
				ostr << '0' << '\t';
			ostr << m.pMem[i] << endl;
		}
		return ostr;
	}
};

template<typename T>
inline TUTriangleMatrix<T>::TUTriangleMatrix(size_t s, const T& val) : TDynamicVector<TDynamicVector<T>>(s)
{
	if (sz > MAX_MATRIX_SIZE)
		throw out_of_range("Matrix size should be less than MAX_MATRIX_SIZE");
	if (sz == 1)
		throw "Triangle Matrix with size 1 doesn't make sense.";
	for (size_t i = 0; i < sz; i++)
		pMem[i] = TDynamicVector<T>(sz - i, val);
}

template<typename T>
inline T& TUTriangleMatrix<T>::operator()(size_t i, size_t j)
{
	return pMem[i][j - i];
}

template<typename T>
inline T& TUTriangleMatrix<T>::at(size_t i, size_t j)
{
	if (pMem == nullptr) throw "pMem is nullptr";
	if (i >= sz) throw out_of_range("index is out of range");
	return pMem[i].at(j - i);
}

template<typename T>
inline const T& TUTriangleMatrix<T>::operator()(size_t i, size_t j) const
{
	return pMem[i][j - i];
}

template<typename T>
inline const T& TUTriangleMatrix<T>::at(size_t i, size_t j) const
{
	if (pMem == nullptr) throw "pMem is nullptr";
	if (i >= sz) throw out_of_range("index is out of range");
	return pMem[i].at(j - i);
}

template<typename T>
inline bool TUTriangleMatrix<T>::operator==(const TUTriangleMatrix<T>& m) const noexcept
{
	return this->TDynamicVector<TDynamicVector<T>>::operator==(m);
}

template<typename T>
inline bool TUTriangleMatrix<T>::operator!=(const TUTriangleMatrix<T>& m) const noexcept
{
	return !(this->operator==(m));
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator*(const T& val)
{
	TUTriangleMatrix tmp(*this);
	for (size_t i = 0; i < sz; i++)
	{
		tmp[i] = tmp[i] * val;
	}
	return tmp;
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator/(const T& val)
{
	TUTriangleMatrix tmp(*this);
	for (size_t i = 0; i < sz; i++)
	{
		tmp[i] = tmp[i] / val;
	}
	return tmp;
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator-(void)
{
	TUTriangleMatrix<T> tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = -(this->operator[](i));
	return tmp;
}

template<typename T>
inline TDynamicVector<T> TUTriangleMatrix<T>::operator*(const TDynamicVector<T>& v)
{
	if (sz != v.size()) throw "Sizes are not equal";
	TDynamicVector<T> tmp(sz);
	for (size_t i = 0; i < sz; i++)
	{
		for (size_t j = i; j < sz; j++)
		{
			tmp[i] = tmp[i] + this->operator()(i, j) * v[j];
		}
	}
	return tmp;
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator+(const TUTriangleMatrix& m)
{
	if (sz != m.size()) throw "Sizes are not equal";
	TUTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = this->operator[](i) + m[i];
	return tmp;
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator-(const TUTriangleMatrix& m)
{

	if (sz != m.size()) throw "Sizes are not equal";
	TUTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = this->operator[](i) - m[i];
	return tmp;
}

template<typename T>
inline TUTriangleMatrix<T> TUTriangleMatrix<T>::operator*(const TUTriangleMatrix& m)
{
	if (sz != m.size()) throw "Sizes are not equal";
	TUTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		for (size_t j = i; j < sz; j++)
			for (size_t k = i; k < sz; k++)
				if (k <= j)
					tmp(i, j) = tmp(i, j) + this->operator()(i, k) * m(k, j);
	return tmp;
}


#endif