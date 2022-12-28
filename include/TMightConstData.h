// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// 
//
//

#ifndef __TMightConstData_H__
#define __TMightConstData_H__

#include <iostream>

using namespace std;

template<typename T>
class TMightConstData
{
protected:
	T data;
	bool isConst = false;
public:
	TMightConstData(const T& _data = T(), bool _isConst = false);

	TMightConstData& Set(const T& _data = T());
	T Get(void) const;
	bool IsConst(void) const;

	TMightConstData& operator=(const T& _data);
	TMightConstData& operator()(const T& _data = T());
	operator T() const;

	friend istream& operator>>(istream& istr, TMightConstData& v)
	{
		if (IsConst())
			throw "Can't change value of a constant.";
		istr >> v.data;
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TMightConstData& v)
	{
		ostr >> v.data;
		return ostr;
	}
};

template<typename T>
inline TMightConstData<T>::TMightConstData(const T& _data, bool _isConst) : data(_data), isConst(_isConst)
{
}

template<typename T>
inline TMightConstData<T>& TMightConstData<T>::Set(const T& _data)
{
	if (IsConst())
		throw "Can't change value of a constant.";
	else
		data = _data;
	return *this;
}

template<typename T>
inline T TMightConstData<T>::Get(void) const
{
	return data;
}

template<typename T>
inline bool TMightConstData<T>::IsConst(void) const
{
	return isConst;
}

template<typename T>
inline TMightConstData<T>& TMightConstData<T>::operator=(const T& _data)
{
	return this->Set(_data);
}

template<typename T>
inline TMightConstData<T>& TMightConstData<T>::operator()(const T& _data)
{
	return this->Set(_data);
}

template<typename T>
inline TMightConstData<T>::operator T() const
{
	return this->Get();
}

#endif