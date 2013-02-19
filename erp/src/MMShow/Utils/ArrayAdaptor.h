#pragma once
#include <vector>

template <typename T>
class CArrayAdaptor
{
public:
	CArrayAdaptor(void) {
	}

	template <class Iter>
	CArrayAdaptor(Iter begin,Iter end)
		:m_pts(begin,end) {
	}

	T* GetData(void) {
		return &m_pts.front();
	}
	const T* GetData(void) const {
		return &m_pts.front();
	}

	int GetCount(void) const {
		return (int)m_pts.size();
	}

	T& operator [](int i) {
		return m_pts[i];
	}

	const T& operator [](int i) const {
		return m_pts[i];
	}

	void Copy(const CArrayAdaptor &pts) {
		m_pts = pts.m_pts;
	}

	BOOL IsEmpty(void) const {
		return m_pts.empty();
	}

	void Add(T pt) {
		m_pts.push_back(pt);
	}

	void InsertAt(int i,T pt) {
		m_pts.insert(m_pts.begin()+i,pt);
	}

	void RemoveAt(int i) {
		m_pts.erase(m_pts.begin() + i);
	}

	void SetSize(int i) {
		m_pts.resize(i);
	}

	void RemoveAll(void) {
		m_pts.clear();
	}
private:
	std::vector<T> m_pts;
};

 

template<class Array,class Elem>
INT_PTR FindIndex(const Array &elems,const Elem &elem)
{
	for (INT_PTR i=0; i<elems.GetCount(); ++i)
		if (elems[i] == elem)
			return i;
	return -1;
}

template<class Elem>
INT_PTR FindIndex(const Elem *elems,INT_PTR size,const Elem &elem)
{
	for (INT_PTR i=0; i<size; ++i)
		if (elems[i] == elem)
			return i;
	return -1;
}
