#pragma once

#include "Multi.h"

class CComposite : public CMulti
{
 
public:
	CComposite(CVecWnd *pWnd = NULL);
	virtual ~CComposite(void);

	DECLARE_TYPE(Composite);
 
	virtual CElem* Clone(void) const; 
	void Decompose(CElems &elems);
 
};
 