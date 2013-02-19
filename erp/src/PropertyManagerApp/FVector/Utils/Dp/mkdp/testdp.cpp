#include "Person.h"

/*
struct _d_struct Person
{
 uint64_t id;
 uint8_t sex;
 Dp::Array<char,32> nick;
 Dp::Array<char,32> address;
 Dp::Array<char,32> memo;
 Dp::Array<int64_t,32> data;
};

struct _d_struct Person1
{
 uint64_t id;
 uint8_t sex;
 Dp::Array<char,32> nick;
 Dp::Array<char,32> address;
 Dp::Array<char,32> memo;
 Dp::Array<int64_t,32> sdata;
 int64_t s11data;
 int64_t s11data;
};
*/

void gen(char *s,int &len)
{
	--len;
	int i = 0;
	for (; i<len-1; ++i)
	{
		s[i] = rand()%('z'-'a') + 'a';
		if (i>4 &&  rand()%3 ==0)
			break;
	}

	s[i] = '\0';
	len = i;
}
 

int main(int argc,char* argv[])
{
	Dp::Array<Person,100> ps;

	for (int i=0; i<10; ++i)
	{
		Person p;
		p.id = i + 5;
		p.sex = i%2;

		char str[32];
		int len = sizeof(str);

		gen(str,len);
		p.nick.assign(str,len);
		
		len = sizeof(str);
		gen(str,len);
		p.address.assign(str,len);
		
		len = sizeof(str);
		gen(str,len);
		p.memo.assign(str,len);
	
		ps.push_back(p);
	}

	Dp::Writer w;
	raw_save_some(w,ps);

	
	Dp::Array<Person1,100> p1s;
	Dp::Reader r(w.ptr(),w.size());

	raw_load_some(r,p1s);

	return 0;
}
