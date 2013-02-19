#ifndef __NUM_X__
#define __NUM_X__

template <int pos>
struct Flag
{
public:
	enum { SetFlag = (1 << pos) };
	enum { UnsetFlag = ~SetFlag };

public:
	template<typename IntType>
	static inline IntType IsSet(IntType val)
	{
		return val & SetFlag;
	}
	
	template<typename IntType>
	static inline IntType IsUnset(IntType val)
	{
		return !(val & SetFlag);
	}

	template<typename IntType>
	static inline IntType Set(IntType val)
	{
		return val | SetFlag;
	}

	template<typename IntType>
	static inline IntType Unset(IntType val)
	{
		return val & UnsetFlag;
	}
};

struct FlagV
{
	template<typename IntType>
	static inline IntType SetFlag(int index)
	{
		return 1 << index;
	}

	template<typename IntType>
	static inline IntType UnsetFlag(int index)
	{
		return ~SetFlag<IntType>(index);
	}

	template<typename IntType>
	static inline IntType IsSet(IntType val,int index)
	{
		return val & SetFlag(index);
	}

	template<typename IntType>
	static inline IntType Set(IntType val,int index)
	{
		return val | SetFlag<IntType>(index);
	}

	template<typename IntType>
	static inline IntType Unset(IntType val,int index)
	{
		return val & UnsetFlag<IntType>(index);
	}

};

template <typename T>
struct KeepSet
{
	KeepSet(T &org,T newVal) 
		: m_orgRef(org) {
		m_valOrg = org;
		m_orgRef = newVal;
	}

	~KeepSet(void) {
		m_orgRef = m_valOrg;
	}

	T m_valOrg;
	T &m_orgRef;
};


inline BOOL RealEqual(REAL l,REAL r)
{
	const float MIN_INC = 0.001f;
	return fabs(l-r) <=0.001f;
}

#endif

