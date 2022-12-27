// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// 
//
//

#ifndef __TDTriangleMatrix_H__
#define __TDTriangleMatrix_H__

#include "tmatrix.h"
#include <iostream>

using namespace std;

template<typename T>
class TDTriangleMatrix : private TDynamicVector<TDynamicVector<T>>
{
protected:
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;

public:
	TDTriangleMatrix(size_t s = 2, const T& val = T());

	using TDynamicVector<TDynamicVector<T>>::size;
	using TDynamicVector<TDynamicVector<T>>::operator[];
	using TDynamicVector<TDynamicVector<T>>::at;
	T& operator()(size_t i, size_t j);
	T& at(size_t i, size_t j);
	const T& operator()(size_t i, size_t j) const;
	const T& at(size_t i, size_t j) const;

	// сравнение
	bool operator==(const TDTriangleMatrix& m) const noexcept;
	bool operator!=(const TDTriangleMatrix& m) const noexcept;

	// скалярные операции
	TDTriangleMatrix operator*(const T& val);
	TDTriangleMatrix operator/(const T& val);
	TDTriangleMatrix operator-(void);

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v);

	// матричные операции
	TDTriangleMatrix operator+(const TDTriangleMatrix& m);
	TDTriangleMatrix operator-(const TDTriangleMatrix& m);
	TDTriangleMatrix operator*(const TDTriangleMatrix& m);

	friend istream& operator>>(istream& istr, TDTriangleMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			istr >> m.pMem[i];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDTriangleMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
		{
			// ostr << m.pMem[i];
			ostr << m.pMem[i];
			for (size_t j = m.pMem[i].size(); j < m.sz; j++)
				// ostr << '0' << ' ';
				ostr << '0' << '\t';
			ostr << endl;
		}
		return ostr;
	}
};

template<typename T>
inline TDTriangleMatrix<T>::TDTriangleMatrix(size_t s, const T& val) : TDynamicVector<TDynamicVector<T>>(s)
{
	if (sz > MAX_MATRIX_SIZE)
		throw out_of_range("Matrix size should be less than MAX_MATRIX_SIZE");
	if (sz == 1)
		throw "Triangle Matrix with size 1 doesn't make sense.";
	for (size_t i = 0; i < sz; i++)
		pMem[i] = TDynamicVector<T>(i + 1, val);
}

template<typename T>
inline T& TDTriangleMatrix<T>::operator()(size_t i, size_t j)
{
	return (this->operator[](i))[j];
}

template<typename T>
inline T& TDTriangleMatrix<T>::at(size_t i, size_t j)
{
	return this->at(i).at(j);
}

template<typename T>
inline const T& TDTriangleMatrix<T>::operator()(size_t i, size_t j) const
{
	return (this->operator[](i))[j];
}

template<typename T>
inline const T& TDTriangleMatrix<T>::at(size_t i, size_t j) const
{
	return this->at(i).at(j);
}

template<typename T>
inline bool TDTriangleMatrix<T>::operator==(const TDTriangleMatrix<T>& m) const noexcept
{
	return this->TDynamicVector<TDynamicVector<T>>::operator==(m);
}

template<typename T>
inline bool TDTriangleMatrix<T>::operator!=(const TDTriangleMatrix<T>& m) const noexcept
{
	return !(this->operator==(m));
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator*(const T& val)
{
	TDTriangleMatrix tmp(*this);
	for (size_t i = 0; i < sz; i++)
	{
		tmp[i] = tmp[i] * val;
	}
	return tmp;
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator/(const T& val)
{
	TDTriangleMatrix tmp(*this);
	for (size_t i = 0; i < sz; i++)
	{
		tmp[i] = tmp[i] / val;
	}
	return tmp;
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator-(void)
{
	TDTriangleMatrix<T> tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = -(this->operator[](i));
	return tmp;
}

template<typename T>
inline TDynamicVector<T> TDTriangleMatrix<T>::operator*(const TDynamicVector<T>& v)
{
	if (sz != v.size()) throw "Sizes are not equal";
	TDynamicVector<T> tmp(sz);
	for (size_t i = 0; i < sz; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			tmp[i] = tmp[i] + this->operator()(i, j) * v[j];
		}
	}
	return tmp;
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator+(const TDTriangleMatrix<T>& m)
{
	if (sz != m.size()) throw "Sizes are not equal";
	TDTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = this->operator[](i) + m[i];
	return tmp;
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator-(const TDTriangleMatrix<T>& m)
{
	if (sz != m.size()) throw "Sizes are not equal";
	TDTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		tmp[i] = this->operator[](i) - m[i];
	return tmp;
}

template<typename T>
inline TDTriangleMatrix<T> TDTriangleMatrix<T>::operator*(const TDTriangleMatrix<T>& m)
{
	if (sz != m.size()) throw "Sizes are not equal";
	TDTriangleMatrix tmp(sz);
	for (size_t i = 0; i < sz; i++)
		for (size_t j = 0; j <= i; j++)
			for (size_t k = 0; k <= i; k++)
				if (k >= j)
					tmp(i, j) = tmp(i, j) + this->operator()(i, k) * m(k, j);
	return tmp;
}

#endif