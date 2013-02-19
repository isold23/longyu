#ifndef __Array__
#define __Array__

#include <stdint.h>
#include "TypesEnum.h"

namespace Dp
{


template<class _Ty,SizeType _Sz>
class Array
{
	typedef Array<_Ty,_Sz> ThisType;
public:
	enum { npos = -1 };
	enum { capacity = _Sz };
	enum { ebytes = sizeof(_Ty) };

public:
	Array(void) : end_(0) { }

	_Ty& operator[](SizeType i) { return vals_[i]; }

	const _Ty& operator[](SizeType i) const { return vals_[i]; }

	SizeType size(void) const { return end_; }
	bool empty(void) const { return end_== 0; }

	SizeType begin(void) const { return 0;}
	SizeType end(void) const { return end_; }

	_Ty* ptr(void) { return vals_; }
	const _Ty* ptr(void) const { return vals_; }

	_Ty* end_ptr(void) { return vals_ + end_; }
	const _Ty* end_ptr(void) const { return vals_ + end_ ; }

	void assign(const _Ty *vals,SizeType c) { if (c>capacity) c=capacity; copy(0,vals,c); end_ = c; }

	void clear(void) { end_ = 0; }

	_Ty& front(void) { return vals_[0]; }
	const _Ty& front(void) const { return vals_[0]; }
	void push_front(const _Ty &val) { if(end_<capacity) { move(1,0,end_) ;vals_[0]=val; ++end_; } }
	void pop_front(void) { --end_; move(0,1,end_); }

	_Ty& back(void) { return vals_[end_-1]; }
	const _Ty& back(void) const { return vals_[end_-1]; }
	void push_back(const _Ty &val) { if( end_<capacity) { vals_[end_++] = val; } }
	void pop_back(void) { --end_; }

	void expand(int32_t count) { count += end_; end_ = (count <= capacity ? count : capacity); }
	void expand_to(SizeType count) { end_ = (count <= capacity ? count : capacity); }

	void insert(SizeType i,const _Ty &val) { if( end_<capacity) { move(i+1,i,end_-i); vals_[i]=val; ++end_;} } 
	void insert(SizeType i,const _Ty *vals,SizeType count) { if( end_+count<capacity) {move(i+count,i,end_-i); copy(i,vals,count); end_+=count ;} }

	void erase(SizeType i) {--end_; move(i,i+1,end_-i);}
	void erase(SizeType i,SizeType c) {end_-=c; move(i,i+c,end_-c);}

	SizeType find(const _Ty &val) const{ SizeType i=0; for (; i<end_ && vals_[i]!=val; ++i); return i!=end_; }

	template <class _Func> void for_each(_Func &f) { for (SizeType i=0; i<end_; ++i) f(vals_[i]); }
	template <SizeType _Sz1> ThisType& operator=(const Array<_Ty,_Sz1> &r) { assign(r.ptr(),r.size()); return *this; }

protected:
	void copy(SizeType d,const _Ty *s,SizeType c) { memcpy(vals_+d,s,c*ebytes); }
	void move(SizeType d,SizeType s,SizeType c) { memmove(vals_+d,vals_+s,c*ebytes); }

	SizeType end_;
	_Ty vals_[_Sz];
};

}
#endif

