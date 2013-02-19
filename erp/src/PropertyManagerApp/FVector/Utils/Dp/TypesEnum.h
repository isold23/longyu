#ifndef __TYPES_ENUM__
#define __TYPES_ENUM__

#include <stdint.h>

namespace Dp
{

struct TypesEnum
{
	enum id
	{
		tid_int8,
		tid_uint8,
		tid_int16,
		tid_uint16,
		tid_int32,
		tid_uint32,
		tid_float,
		tid_int64,
		tid_uint64,
		tid_double,
		tid_array,
		tid_buffer,
		tid_string,
		tid_wstring,
		tid_stdstr,
		tid_stdwstr
	};

	enum size
	{
		size_8 = 0,
		size_16 = 1,
		size_32 = 2,
		size_64 = 3,
		size_array = 4
	};
};

inline uint8_t memberId(uint8_t flag) {
	return (flag >> 3); 
}

inline uint8_t memberSize(uint8_t flag) {
	return (flag & 0x7); 
}

inline uint8_t makeMemberFlag(uint8_t id,uint8_t size) {
	return (id <<3 | size);
}

typedef uint32_t SizeType;

}

#endif

