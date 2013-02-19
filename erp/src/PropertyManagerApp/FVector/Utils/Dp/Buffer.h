#ifndef ____BF____
#define ____BF____

namespace Dp
{

template <class _Ty>
class Buffer
{
public: 
	Buffer(void) :ptr_(NULL),cnt_(0) { }
	Buffer(const _Ty *vals,Dp::SizeType cnt) :ptr_(vals),cnt_(cnt) { }

	void reset(const void *p,Dp::SizeType cnt) { ptr_ = (_Ty*)p; cnt_ = cnt; }
 
	_Ty* ptr(void) { return const_cast<_Ty*>(ptr_); }
	const _Ty* ptr(void) const { return ptr_; }
	Dp::SizeType size(void) const { return cnt_; }

	bool null(void) const { return (ptr_ == NULL); }
	bool empty(void) const { return (null() || cnt_==0); }

	void append(const void *p,SizeType cnt) { ::memcpy(ptr()+cnt_,p,sizeof(_Ty)*cnt); }

private:
	const _Ty *ptr_;
	SizeType cnt_;
};

template<class _Em>
inline Buffer<_Em> make_buffer(const _Em *vals,Dp::SizeType count) {
	return Buffer<_Em>(vals,count);
}

}

#endif
