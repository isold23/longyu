#include "stdafx.h"
#include "Composite.h"
#include "resource.h"
#include "VecWnd.h"
#include "PathHelper.h"
#include "GraphAlgorithm.h"


CComposite::CComposite(CVecWnd *pWnd)
	: CMulti(pWnd)
{

}

CComposite::~CComposite(void)
{
	for (int i=0; i<m_elems.GetCount(); ++i)
		delete m_elems[i];
	m_elems.RemoveAll();
}
 

CElem* CComposite::Clone(void) const 
{
	return NULL;
	//CComposite *pComposite = new CComposite(m_pWnd);
	//pComposite->m_elems.SetSize(m_elems.GetCount());
	//for (int i=0; i<pComposite->m_elems.GetCount(); ++i)
	//	pComposite->m_elems[i] = m_elems[i]->Clone();
	//return pComposite;
}

 
void CComposite::Decompose(CElems &elems)
{
	elems.Copy(m_elems);
	m_elems.RemoveAll();
}