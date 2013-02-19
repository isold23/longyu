#pragma once
#include "VecParam.h"
#include "../Elem.h"
#include "../../Utils/Dp/Bs.h"

class CElem;
class CFilled;
class COutlined;

class CBinVecLS
{
public:
	static BOOL Load(LPCTSTR pcszFileName,stVecParam &param,CElems &elems);
	static BOOL Save(LPCTSTR pcszFileName,const stVecParam &param,const CElems &elems);

private:
	static CElem* LoadElem(Dp::Reader &r);
	template <class WRITER>
	static void SaveElem(const CElem *pElem,WRITER &w);

	static void LoadVecElem(CFilled *pElem,Dp::Reader &r);
	template <class WRITER>
	static void SaveVecElem(const CFilled *pElem,WRITER &w);

	static void LoadNonFillVecElem(COutlined *pElem,Dp::Reader &r);
	template <class WRITER>
	static void SaveNonFillVecElem(const COutlined *pElem,WRITER &w);
};

