#pragma once
#include "merize.h"

#if 0
//types for quick switching between arrays/stdvectors without having to modify code

class hybridarray_base
{
public:
	virtual int size() = 0;
	int arraysafety(int spot);
};

//traditional c array
template <typename Type>
class hybridarray_static : hybridarray_base
{
public:

	Type* m_Array;
public:
	virtual int size() { return m_Size; }
	hybridarray_static(int size)
	{
		m_Array = new Type[size];
		m_Size = size;
	}
	Type operator [] (int i)
	{
		i = arraysafety(i);
		return m_Array[i];
	}
private:
	int m_Size;
};



//vector version
template <typename Type>
class hybridarray_dynamic : hybridarray_base
{
public:

	stdvector<Type> m_Vector;
public:
	virtual int size() { return m_Vector.size(); }
	hybridarray_dynamic(int size)
	{
		//reserve spots in the vector
		m_Vector.reserve(size);
	}
	Type operator [] (int i)
	{
		i = arraysafety(i);
		return m_Vector[i];
	}
};


//vector version. CANNOT go past m_Size. use this when you want an array that uses the least amount of memory possible
template <typename Type>
class hybridarray_dynamic_tight : hybridarray_base
{
public:

	stdvector<Type> m_Vector;
public:
	virtual int size() { return m_Vector.size(); }
	hybridarray_dynamic_tight(int size)
	{
		//reserve spots in the vector
		m_Size = size;
	}
	Type operator [] (int i)
	{
		if (i > size() && i < m_Size)
		{
			m_Vector.reserve(i);
		}
		i = arraysafety(i);
		return m_Vector[i];
	}
private:
	int m_Size;
};


#endif