#ifndef __STRING____
#define __STRING____

#include "Array.h"
namespace Dp
{

template<class _Ty,SizeType _Sz>
class StringT
{
	typedef StringT<_Ty,_Sz> ThisType;
public:
	enum { npos = -1 };
	enum { capacity = _Sz };
	enum { ebytes = sizeof(_Ty) };

	typedef _Ty Char;
	typedef _Ty* PChar;
	typedef const _Ty* CPChar;

public:
	StringT(void) { tail(); }
	StringT(const _Ty *vals) { assign(vals); }
	StringT(const _Ty *vals,Dp::SizeType len) { assign(vals,len); }

	_Ty& operator[](SizeType i) { return vals_[i]; }

	const _Ty& operator[](SizeType i) const { return vals_[i]; }

	SizeType size(void) const { return vals_.size(); }
	bool empty(void) const { return vals_.empty(); }

	SizeType begin(void) const { return vals_.begin();}
	SizeType end(void) const { return vals_.end(); }

	_Ty* ptr(void) { return vals_.ptr(); }
	const _Ty* ptr(void) const { return vals_.ptr(); }

	_Ty* end_ptr(void) { return vals_.end_ptr(); }
	const _Ty* end_ptr(void) const { return vals_.end_ptr(); }

	void assign(const _Ty *vals,SizeType c) { vals_.assign(vals,c); tail(); }

	void clear(void) { vals_.clear(); tail(); }

	_Ty& front(void) { return vals_.front(); }
	const _Ty& front(void) const { return vals_.front(); }
	void push_front(const _Ty &val) { vals_.push_front(val); tail(); }
	void pop_front(void) { vals_.pop_front(); tail(); }

	_Ty& back(void) { return vals_.back(); }
	const _Ty& back(void) const { return vals_.back(); }
	void push_back(const _Ty &val) { vals_.push_back(val); tail(); }
	void pop_back(void) { vals_.pop_back(); tail(); }

	void expand(int32_t count) { vals_.expand(count); tail(); }
	void expand_to(SizeType count) { vals_.expand_to(count); tail(); }

	void insert(SizeType i,const _Ty &val) { vals_.insert(i,val); tail(); } 
	void insert(SizeType i,const _Ty *vals,SizeType count) { vals_.insert(i,vals,count); tail(); }

	void erase(SizeType i) { vals_.erase(i); tail(); }
	void erase(SizeType i,SizeType c) { vals_.erase(i,c); tail(); }

	SizeType find(const _Ty &val) const { return vals_.find(val); }

	template <class _Func> void for_each(_Func &f) { vals_.for_each(f); }
	template <SizeType _Sz1> ThisType& operator=(const StringT<_Ty,_Sz1> &r) { assign(r.ptr(),r.size()); return *this; }

	void assign(const _Ty *s) { int i = 0; while (s[i++]); assign(s,i-1); }

protected: 
	void tail(void) { vals_[vals_.size()==_Sz+1 ? _Sz : vals_.size()] = 0; }

	Array<_Ty,_Sz+1> vals_;
};

template <Dp::SizeType _Sz> class String : public StringT<char,_Sz> 
{
    typedef StringT<char,_Sz> Base;
public:
	String(void) {}
	String(const char *s) : Base(s) { }
	String(const char *s,Dp::SizeType len) : Base(s,len) { }
};
template <Dp::SizeType _Sz> class WString : public StringT<wchar_t,_Sz> 
{
    typedef StringT<wchar_t,_Sz> Base;
public:
	WString(void) {}
	WString(const wchar_t *s) : Base(s) { }
	WString(const wchar_t *s,Dp::SizeType len) : Base(s,len) { }

};


}

#endif
