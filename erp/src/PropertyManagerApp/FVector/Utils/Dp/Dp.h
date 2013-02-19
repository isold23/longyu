#ifndef ___d_define__
#define ___d_define__

#include "Bs.h"

#define _def(x)

// Dynamic
#define _d_struct 
#define _d_id(x)
#define _d_serializable_impl(struct_name) \
	struct_name(void); \
	bool load(Dp::Reader &r); \
	void save(Dp::Writer &w);

// Fixed
#define _f_struct
#define _f_f
#define _f_d
#define _f_a
#define _f_s

template <class _Tx,uint32_t _Sz>
uint32_t raw_load_some(Dp::Reader &r,Dp::Array<_Tx,_Sz> &structs) {
	Dp::SizeType sz; r >> sz;
	Dp::SizeType i = 0;

	for (; i<sz && i<_Sz; ++i) {
		_Tx t; t.load(r);
		if (!r.ok()) return -1;
		structs.push_back(t);
	}
	return sz - i;
}

template <class _Tx,uint32_t _Sz>
void raw_save_some(Dp::Writer &w,Dp::Array<_Tx,_Sz> &structs) {
	w << (Dp::SizeType)structs.size();
	for (uint32_t i = 0; i<structs.size(); ++i)
		structs[i].save(w);
}

#endif
