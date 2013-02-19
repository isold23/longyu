#include "../Dp.h"

struct _d_struct Person
{
	_d_serializable_impl(Person)

	_d_id(-) uint64_t id;
	_d_id(-) uint8_t sex;
	_d_id(-) Dp::Array<char,32> nick;
	_d_id(-) Dp::Array<char,32> address;
	_d_id(21) uint32_t stuv _def(222);
	_d_id(1) Dp::Array<char,32> memo;
	_d_id(2) Dp::Array<int64_t,32> data;
	_d_id(10) Dp::String<32> he _def("hellow this is!!!");
	_d_id(11) std::string hafasf _def("xxxxxxA");
};

struct _d_struct Person1
{
	_d_serializable_impl(Person1)

	_d_id(-) uint64_t id;
	_d_id(-) uint8_t sex;
	_d_id(-) Dp::Array<char,32> nick;
	_d_id(-) Dp::Array<char,32> address;
	_d_id(1) Dp::Array<char,32> memo;
	_d_id(3) Dp::Array<int64_t,32> sdata;
	_d_id(4) int64_t s11data;	
	_d_id(5) int64_t hdata;
	_d_id(10) Dp::String<32> he;
	_d_id(11) std::string hafasf;;
};

struct _f_struct tagPerson
{
	_d_serializable_impl(tagPerson)

	_f_f uint16_t ver _def(0);
	_f_f uint16_t len _def(0);
	_f_f uint32_t cmd _def(8);
	
	_f_d Person1 p1;
	_f_a Dp::Array<Person,100> ps;
	_f_s Dp::Array<Person,100> ps1;
};

#include "Person.inl"
//inline Dp::Reader& operator >> (Dp::Reader& r,Person &elem) 
//{
//	elem.load(r);
//	return r;
//}
//
//inline Dp::Writer& operator << (Dp::Writer& w,Person &elem) 
//{
//	elem.save(w); return w;
//}
//
//template<Dp::SizeType _Sz>
//Dp::Reader& operator >> (Dp::Reader& r,Dp::Array<Person,_Sz> &elems) 
//{
//	load_some(r,elems)
//	return r;
//}
//
//template<Dp::SizeType _Sz>
//Dp::Writer& operator << (Dp::Writer& w,const Dp::Array<Person,_Sz> &elems) 
//{
//	save_some(w,elems);
//	return w;
//}



