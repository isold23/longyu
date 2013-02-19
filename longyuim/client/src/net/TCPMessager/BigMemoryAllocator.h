/*
FlyNet
Copyright (C) 2005  author:lu_zi

这一函数库是自由软体，您可以遵照自由软体基金会出版的 GNU GENERAL PUBLIC LICENSE
条款来修改和重新发布这一程式，或者用许可证的第二版，或者 (根据您的选择)
用任何更新的版本。

发布这一函数库的目的是希望它有用，但没有任何担保。甚至没有适合特定目的而隐含的
担保。更详细的情况请参阅 GNU General Public License。

有任何问题请发邮件至:lu_zi@msn.com
*/
#ifndef __BIG_MEMORY__
#define __BIG_MEMORY__

#include <list>

using namespace std;

//#include <boost/thread.hpp>

//using namespace boost;

template<int size>
class CBigMemoryAllocator
{
public:
	CBigMemoryAllocator(){}
  ~CBigMemoryAllocator()
    {
      for(list<unsigned char*>::iterator iter=m_buffer.begin();iter!=m_buffer.end();iter++)
	{
	  if(*iter)
            {
	      delete (*iter);
            }
        }
    }
 protected:
  list<unsigned char*> m_buffer;
  //mutex m_mutex;
 public:
  unsigned char* GetBuffer()
    {
     // mutex::scoped_lock lock(m_mutex);
      if(m_buffer.size())
        {
	  unsigned char* p=*m_buffer.begin();
	  m_buffer.pop_front();
	  return p;
        }
      return new unsigned char[size];
    }
  void ReturnBuffer(unsigned char* p)
  {
    m_buffer.push_back(p);
  }
};
 
#endif//__BIG_MEMORY__
