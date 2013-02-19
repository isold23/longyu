#pragma once
#include "VecParam.h"
#include "..\ElemInc.h"
#include "../../Utils/XMLDoc.h"

class CXMLVecLS
{

public:
	static BOOL Load(LPCTSTR pcszFileName,stVecParam &param,CElems &elems);
	static BOOL Save(LPCTSTR pcszFileName,const stVecParam &param,const CElems &elems);

private:
	static int GetType(LPCTSTR pcszTypeName);
	static LPCTSTR GetTypeName(int nType);

	static void SaveElem(const CElem *pElem,CXmlNode &node);
	static CElem* LoadElem(CXmlNode &node);

	static void SaveFilledVecElem(const CFilled *pElem,CXmlNode &node);
	static BOOL LoadFilledVecElem(CFilled *pElem,CXmlNode &node);

	static void SaveNonFillVecElem(const COutlined *pElem,CXmlNode &node);
	static BOOL LoadNonFillVecElem(COutlined *pElem,CXmlNode &node);



	static LPCTSTR s_pcszVecTypes[];
};

