#ifndef __BINARY_STREAM__
#define __BINARY_STREAM__

#include <cstdlib>
#include <memory.h>
#include <vector>
#include <string>
#include "TypesEnum.h"
#include "Array.h"
#include "Buffer.h"
#include "String.h"

namespace Dp
{

class Reader;
class Writer;

class Reader
{ 
	Reader(const Reader &);

public:
	template<class _Ty>void get(_Ty*);
	template<class _Ty>void get(const _Ty*);

	Reader(const void *buf,SizeType sz)
		: good_(true),cursor_(0),size_(sz),
		  buffer_((const unsigned char*)(buf)) {
	}
 
	const unsigned char* ptr(void) const {
		return buffer_;
	}

 	SizeType cursor(void) const { 
		return cursor_;
	}

	SizeType size(void) const {
		return size_;
	}

	SizeType left(void) const {
		return size_ - cursor_;
	}

	bool ok(void) const {
		return good_;
	}

	void reok(bool flag) {
		good_ = flag;
	}

	void skip(SizeType cb) {
		if (good_) {
			if (cursor_ + cb > size_)
				good_ = false;
			else
				cursor_ += cb;
		}
	}

	template<class _Ty> void get(_Ty &t) { 
		*this >> t;
	}

	template<class _Ty> Reader& operator >> (_Ty &t) {
		if (good_) {
			SizeType cb = sizeof(_Ty);
			SizeType c = cursor_ + cb;
			if (c > size_) {
				good_ = false;
			} 
			else {
				t = *(const _Ty*)(buffer_+cursor_);
				cursor_ = c;
			}
		}
		return *this;
	}

	void get(void *buf,SizeType cb) { 
		if (good_) {
			SizeType c = cursor_ + cb;
			if (c > size_) {
				good_ = false;
			} 
			else {
				memcpy(buf,buffer_+cursor_,cb);
				cursor_  = c;
			}
		}
	}

	template<class _Em>
	Reader& operator >> (Buffer<_Em> &b) {
		if (good_) {
			if (cursor_+sizeof(SizeType) > size_) {
				good_ = false;
			}
			else {
				SizeType sz; get(sz);
				if (cursor_+sz > size_) {
					cursor_ -= sizeof(SizeType);
					good_ = false;
				}
				else {
					b.reset((const _Em*)(buffer_+cursor_),sz/sizeof(_Em));
					cursor_ += sz;
				}
			}
		}
		return *this;
	}

	template<class _Em,SizeType _Sz> 
	Reader& operator >> (Array<_Em,_Sz> &t) { 
		if (good_) {
			Buffer<_Em> b;
			SizeType oldCursor = cursor_;
			*this >> b;
			if (good_)
				t.assign(b.ptr(),b.size());
			else
				cursor_ = oldCursor;
		}
		return *this;
	}

	template<SizeType _Sz> 
	Reader& operator >> (String<_Sz> &t) { 
		if (good_) {
			Buffer<char> b;
			SizeType oldCursor = cursor_;
			*this >> b;
			if (good_)
				t.assign(b.ptr(),b.size());
			else
				cursor_ = oldCursor;
		}		return *this;
	}

	template<SizeType _Sz> 
	Reader& operator >> (WString<_Sz> &t) { 
		if (good_) {
			Buffer<wchar_t> b;
			SizeType oldCursor = cursor_;
			*this >> b;
			if (good_)
				t.assign(b.ptr(),b.size());
			else
				cursor_ = oldCursor;
		}
		return *this;
	}

	Reader& operator >> (std::string &t) { 
		if (good_) {
			Buffer<char> b;
			*this >> b;
			if (good_)
				t.assign(b.ptr(),b.size());
		}
		return *this;
	}
	
	Reader& operator >> (std::wstring &t) { 
		if (good_) {
			Buffer<wchar_t> b;
			*this >> b;
			if (good_)
				t.assign(b.ptr(),b.size());
		}
		return *this;
	}

private:
	bool good_;
	SizeType cursor_;
	SizeType size_;
	const unsigned char *buffer_;
};

 
class Writer  
{
	enum { stack_size = 8*1024 };

	Writer(const Writer&);

public:
	template<class _Ty>void put(_Ty*);
	template<class _Ty>void put(const _Ty*);

	Writer(void) { }

	SizeType size(void) const{
		return (heap_buffer_.empty() ? (SizeType)stack_buffer_.size() : (SizeType)heap_buffer_.size());
	}

	SizeType cursor(void) const {
		return size();
	}
	
	unsigned char* ptr(void) {	// This pointer cann't be stored for later use
		return (heap_buffer_.empty() ? stack_buffer_.ptr() : & heap_buffer_.front()); 
	}

	const unsigned char* ptr(void) const {	// This pointer cann't be stored for later use
		return (heap_buffer_.empty() ? stack_buffer_.ptr() : & heap_buffer_.front()); 
	}
 
	void set(SizeType i,const void *buf,SizeType cb) {
		memcpy(ptr()+i,buf,cb);
	}

	template<class _Ty>
	void set(SizeType i,const _Ty &t) {
		set(i,&t,sizeof(_Ty));
	}
 
	void skip(SizeType cb) {
		if (heap_buffer_.empty())
			stack_buffer_.expand(cb);
		else
			heap_buffer_.insert(heap_buffer_.end(),cb,0);
  	}
 
	template<class _Ty> void put(const _Ty &t) {
		*this << t;
	}

	template<class _Ty> Writer& operator << (const _Ty &t) {
		put(&t,sizeof(_Ty));
		return *this;
	} 

	void put(const void *buf,SizeType cb) { 
		const unsigned char *b = static_cast<const unsigned char*>(buf);
		if (heap_buffer_.empty() && stack_buffer_.size() + cb < stack_buffer_.capacity) {
			stack_buffer_.insert(stack_buffer_.end(),b,cb);
		}
		else {
			if (heap_buffer_.empty()) {
				heap_buffer_.reserve(stack_size*2);
				if (!stack_buffer_.empty())
					heap_buffer_.insert(heap_buffer_.end(),stack_buffer_.ptr(),stack_buffer_.end_ptr());
			}
			heap_buffer_.insert(heap_buffer_.end(),b,b+cb);
		}
	}

	template<class _Em>
	Writer& operator << (const Buffer<_Em> &b) {
		SizeType sz = b.size()*sizeof(_Em);
		put(sz);
		put(b.ptr(),sz);
		return *this;
	}

	template<class _Em,SizeType _Sz>
	Writer& operator << (const Array<_Em,_Sz> &t) { 
		*this << make_buffer(t.ptr(),t.size());
		return *this;
	}

	template<SizeType _Sz>
	Writer& operator << (const String<_Sz> &t) { 
		*this << make_buffer(t.ptr(),t.size());
		return *this;
	}

	template<SizeType _Sz>
	Writer& operator << (const WString<_Sz> &t) { 
		*this << make_buffer(t.ptr(),t.size());
		return *this;
	}

	Writer& operator << (const std::string &t) { 
		*this << make_buffer(t.c_str(),(Dp::SizeType)t.size());
		return *this;
	}

	Writer& operator << (const std::wstring &t) { 
		*this << make_buffer(t.c_str(),(Dp::SizeType)t.size());
		return *this;
	}

private:
	std::vector<unsigned char> heap_buffer_;
	Array<unsigned char,stack_size> stack_buffer_;
};


} 

#endif

