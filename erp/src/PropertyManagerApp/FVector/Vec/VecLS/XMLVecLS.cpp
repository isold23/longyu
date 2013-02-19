#include "stdafx.h"
#include  "XMLVecLS.h"
#ifndef TEST_FREE_RETURNNULL
#define TEST_FREE_RETURNNULL(con,x) if (con){delete x; return NULL;}
#endif


LPCTSTR CXMLVecLS::s_pcszVecTypes[] = {
	NULL,_T("Line"),_T("FreeLine"),_T("Bezier"),
	_T("Region"),_T("Arc"),_T("Poly"),
	_T("Rectangle"),_T("Ellipse"),_T("Chord"),
	_T("Pie")
};


inline int CXMLVecLS::GetType(LPCTSTR pcszTypeName)
{
	for (int i=1; i<_countof(s_pcszVecTypes); ++i)
	{
		if (_tcscmp(pcszTypeName,s_pcszVecTypes[i]) == 0)
			return i;
	}

	return CElem::UnknownElem;
}

inline LPCTSTR CXMLVecLS::GetTypeName(int nType)
{
	ASSERT(nType>=CElem::Line && nType<=CElem::Pie);
	return s_pcszVecTypes[nType];
}


BOOL CXMLVecLS::Load(LPCTSTR pcszFileName,stVecParam &param,CElems &elems)
{
	CXmlDoc file;
	if (!file.Load(pcszFileName))
		return FALSE;

	CElem *pElem;

	CXmlNode n;
	CXmlNode node = file.Root;
	param.strBkgndImage = node.GetStringAttrib(_T("BkgndImage"));
	param.clrBk = node.GetUIntAttrib(_T("BkColor"));
	param.dwCustomData = node.GetBigUIntAttrib(_T("CustomData"));
	param.strDesc = node.GetStringAttrib(_T("Desc"));
	param.scale.cx = node.GetFloatAttrib(_T("XScale"));
	param.scale.cy = node.GetFloatAttrib(_T("YScale"));

	BOOL err = FALSE;
	for (int i=0,cnt=node.ChildCount; i<cnt && !err; ++i)
	{
		n = node.Child[i];
		pElem = LoadElem(n);
		if (pElem != NULL)
			elems.Add(pElem);
		else 
			err = TRUE;
	}

	if (!err)
		return TRUE;
	
	for (int i=0; i<elems.GetCount(); ++i)
		delete elems[i];
	elems.RemoveAll();
	return FALSE;

}

BOOL CXMLVecLS::Save(LPCTSTR pcszFileName,const stVecParam &param,const CElems &elems)
{
	CXmlDoc file;
	VERIFY(file.SetText(_T("<Vector/>")));

	CXmlNode node = file.GetRoot();
	node.SetAttrib(_T("BkgndImage"),param.strBkgndImage);
	node.SetAttrib(_T("BkColor"),param.clrBk);
	node.SetAttrib(_T("CustomData"),(ULONGLONG)param.dwCustomData);
	node.SetAttrib(_T("Desc"),param.strDesc);
	node.SetAttrib(_T("XScale"),param.scale.cx);
	node.SetAttrib(_T("YScale"),param.scale.cy);

	for (int i=0; i<elems.GetCount(); ++i)
	{
		SaveElem(elems[i],node);
	}

	return file.Save(pcszFileName);
}



void CXMLVecLS::SaveElem(const CElem *pElem,CXmlNode &node)
{
	CRectF rc; 
	int nType = pElem->GetType();
	LPCTSTR pcszTypeName =  GetTypeName(nType);
	CXmlNode n = node.AppendChild(pcszTypeName);

	if (pElem->GetCustomData() != 0)
		n.SetAttrib(_T("CustomData"),(ULONGLONG)pElem->GetCustomData());
	if (!pElem->GetDesc().IsEmpty())
		n.SetAttrib(_T("Desc"),pElem->GetDesc());
	//n.SetAttrib(_T("TextColor"),pElem->GetTextColor());
	//n.SetAttrib(_T("Text"),pElem->GetText());

	switch (nType)
	{
	case CElem::Line:
		{
			const CLine *elem = static_cast<const CLine*>(pElem);

			SaveNonFillVecElem(elem,n);
			n.SetAttrib(_T("StartPointX"),elem->GetStartPoint().x);
			n.SetAttrib(_T("StartPointY"),elem->GetStartPoint().y);
			n.SetAttrib(_T("EndPointX"),elem->GetEndPoint().x);
			n.SetAttrib(_T("EndPointY"),elem->GetEndPoint().y); 
		}
		break;
	case CElem::Bezier:
		{
			const CBezier *elem = static_cast<const CBezier*>(pElem);
			SaveNonFillVecElem(elem,n);

			CXmlNode nPt;
			const CFPoints &pts = elem->GetPoints();
			for (int i=0; i<(int)pts.GetCount(); ++i)
			{
				nPt = n.AppendChild(_T("Point"));
				nPt.SetAttrib(_T("X"),pts[i].x);
				nPt.SetAttrib(_T("Y"),pts[i].y);
			}
		}
		break;
	case CElem::FreeLine:
		{
			const CFreeLine *elem = static_cast<const CFreeLine*>(pElem);
			SaveNonFillVecElem(elem,n);

			CXmlNode nPt;
			const CFPoints &pts = elem->GetPoints();
			for (int i=0; i<(int)pts.GetCount(); ++i)
			{
				nPt = n.AppendChild(_T("Point"));
				nPt.SetAttrib(_T("X"),pts[i].x);
				nPt.SetAttrib(_T("Y"),pts[i].y);
			}
		}
	case CElem::Arc:
		{
			const CArc *elem = static_cast<const CArc*>(pElem);
			SaveNonFillVecElem(elem,n);

			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
			n.SetAttrib(_T("StartAngel"),elem->GetStartAngel());
			n.SetAttrib(_T("EndAngel"),elem->GetEndAngel()); 
		}
		break;
	case CElem::Poly:
		{
			const CPoly *elem = static_cast<const CPoly*>(pElem);
			SaveFilledVecElem(elem,n);

			CXmlNode nPt;
			const CFPoints &pts = elem->GetPoints();
			for (int i=0; i<(int)pts.GetCount(); ++i)
			{
				nPt = n.AppendChild(_T("Point"));
				nPt.SetAttrib(_T("X"),pts[i].x);
				nPt.SetAttrib(_T("Y"),pts[i].y);
			}
		}
		break;
	case CElem::Region:
		{
			const CRegion *elem = static_cast<const CRegion*>(pElem);
			SaveFilledVecElem(elem,n);

			CXmlNode nPt;
			const CFPoints &pts = elem->GetPoints();
			for (int i=0; i<(int)pts.GetCount(); ++i)
			{
				nPt = n.AppendChild(_T("Point"));
				nPt.SetAttrib(_T("X"),pts[i].x);
				nPt.SetAttrib(_T("Y"),pts[i].y);
			}
		}
		break;
	case CElem::Rectangle:
		{
			const CRectangle *elem = static_cast<const CRectangle*>(pElem);
			SaveFilledVecElem(elem,n);

			if (!elem->GetText().IsEmpty())
				n.SetAttrib(_T("Text"),elem->GetText());
			if (elem->GetTextColor() != 0)
				n.SetAttrib(_T("TextColor"),elem->GetTextColor());
			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
		}
		break;
	case CElem::RoundRect:
		{
			const CRoundRect *elem = static_cast<const CRoundRect*>(pElem);
			SaveFilledVecElem(elem,n);

			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
			n.SetAttrib(_T("XEllipse"),elem->GetXEllipse());
			n.SetAttrib(_T("YEllipse"),elem->GetYEllipse()); 
		}
		break;
	case CElem::Ellipse:
		{
			const CEllipse *elem = static_cast<const CEllipse*>(pElem);
			SaveFilledVecElem(elem,n);

			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
		}
		break;
	case CElem::Chord:
		{
			const CChord *elem = static_cast<const CChord*>(pElem);
			SaveFilledVecElem(elem,n);

			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
			n.SetAttrib(_T("StartAngel"),elem->GetStartAngel());
			n.SetAttrib(_T("EndAngel"),elem->GetEndAngel()); 
		}
		break;
	case CElem::Pie:
		{
			const CChord *elem = static_cast<const CChord*>(pElem);
			SaveFilledVecElem(elem,n);

			elem->GetBoundsRect(rc);
			n.SetAttrib(_T("RectLeft"),rc.left);
			n.SetAttrib(_T("RectTop"),rc.top);
			n.SetAttrib(_T("RectRight"),rc.right);
			n.SetAttrib(_T("RectBottom"),rc.bottom);
			n.SetAttrib(_T("StartAngel"),elem->GetStartAngel());
			n.SetAttrib(_T("EndAngel"),elem->GetEndAngel()); 

		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

CElem* CXMLVecLS::LoadElem(CXmlNode &node)
{
	CString str;
	int nType = GetType(node.GetName());

	CPointF pt;
	CRectF rc; 

	CElem *elem = NULL;
	switch (nType)
	{
	case CElem::Line:
		{		
			CLine *pElem = new CLine();
			
			TEST_FREE_RETURNNULL(!LoadNonFillVecElem(pElem,node),pElem);
 
			pt.x = node.GetFloatAttrib(_T("StartPointX"));
			pt.y = node.GetFloatAttrib(_T("StartPointY"));
			pElem->SetStartPoint(pt);

			pt.x = node.GetFloatAttrib(_T("EndPointX"));
			pt.y = node.GetFloatAttrib(_T("EndPointY")); 
			pElem->SetEndPoint(pt);
			elem = pElem;
		}
		break;
	case CElem::Bezier:
		{		
			CBezier *pElem = new CBezier();
			
			TEST_FREE_RETURNNULL(!LoadNonFillVecElem(pElem,node),pElem);

			CXmlNode n;
			CPointF pt;
			CFPoints pts;
			for (int i=0,cnt=node.ChildCount; i<cnt; ++i)
			{
				n = node.Child[i];
				if (n.GetName() == _T("Point"))
				{
					pt.x = n.GetFloatAttrib(_T("X"));
					pt.y = n.GetFloatAttrib(_T("Y"));
					pts.Add(pt);
				}
			}
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::FreeLine:
		{		
			CFreeLine *pElem = new CFreeLine();
			
			TEST_FREE_RETURNNULL(!LoadNonFillVecElem(pElem,node),pElem);

			CXmlNode n;
			CPointF pt;
			CFPoints pts;
			for (int i=0,cnt=node.ChildCount; i<cnt; ++i)
			{
				n = node.Child[i];
				if (n.GetName() == _T("Point"))
				{
					pt.x = n.GetFloatAttrib(_T("X"));
					pt.y = n.GetFloatAttrib(_T("Y"));
					pts.Add(pt);
				}
			}
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::Arc:
		{
			CArc *pElem = new CArc();
			
			TEST_FREE_RETURNNULL(!LoadNonFillVecElem(pElem,node),pElem);

			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);

			pElem->SetStartAngel(node.GetFloatAttrib(_T("StartAngel")));
			pElem->SetEndAngel(node.GetFloatAttrib(_T("EndAngel")));

			elem = pElem;
		}
		break;
	case CElem::Chord:
		{
			CChord *pElem = new CChord();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);

			pElem->SetStartAngel(node.GetFloatAttrib(_T("StartAngel")));
			pElem->SetEndAngel(node.GetFloatAttrib(_T("EndAngel")));
			elem = pElem; 
		}
		break;
	case CElem::Pie:
		{
			CPie *pElem = new CPie();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);

			pElem->SetStartAngel(node.GetFloatAttrib(_T("StartAngel")));
			pElem->SetEndAngel(node.GetFloatAttrib(_T("EndAngel")));
			elem = pElem;  
		}
		break;

	case CElem::Poly:
		{
			CPoly *pElem = new CPoly();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			CXmlNode n;
			CPointF pt;
			CFPoints pts;
			for (int i=0,cnt=node.ChildCount; i<cnt; ++i)
			{
				n = node.Child[i];
				if (n.GetName() == _T("Point"))
				{
					pt.x = n.GetFloatAttrib(_T("X"));
					pt.y = n.GetFloatAttrib(_T("Y"));
					pts.Add(pt);
				}
			}
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::Region:
		{
			CRegion *pElem = new CRegion();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			CXmlNode n;
			CPointF pt;
			CFPoints pts;
			for (int i=0,cnt=node.ChildCount; i<cnt; ++i)
			{
				n = node.Child[i];
				if (n.GetName() == _T("Point"))
				{
					pt.x = n.GetFloatAttrib(_T("X"));
					pt.y = n.GetFloatAttrib(_T("Y"));
					pts.Add(pt);
				}
			}
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::Rectangle:
		{			
			CRectangle *pElem = new CRectangle();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			pElem->SetText(node.GetStringAttrib(_T("Text")));
			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);
			elem = pElem;
		}
		break;
	case CElem::RoundRect:
		{
			CRoundRect *pElem = new CRoundRect();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);

			pElem->SetXEllipse(node.GetFloatAttrib(_T("XEllipse")));
			pElem->SetYEllipse(node.GetFloatAttrib(_T("YEllipse")));

			elem = pElem;
		}
		break;
	case CElem::Ellipse:
		{
			CEllipse *pElem = new CEllipse();
			
			TEST_FREE_RETURNNULL(!LoadFilledVecElem(pElem,node),pElem);

			rc.left = node.GetFloatAttrib(_T("RectLeft"));
			rc.top = node.GetFloatAttrib(_T("RectTop"));
			rc.right = node.GetFloatAttrib(_T("RectRight"));			
			rc.bottom = node.GetFloatAttrib(_T("RectBottom"));
			pElem->SetBoundsRect(rc);

			elem = pElem;;
		}
		break;
	default: 
		ASSERT(FALSE);
		return NULL;
	} 
	if (elem != NULL)
	{
		elem->SetCustomData(node.GetBigUIntAttrib(_T("CustomData")));
		elem->SetDesc(node.GetStringAttrib(_T("Desc")));
		//elem->SetText(node.GetStringAttrib(_T("Text")));
		//elem->SetTextColor(node.GetUIntAttrib(_T("TextColor")));
	}

	return elem;
}


void  CXMLVecLS::SaveFilledVecElem(const CFilled *pElem,CXmlNode &node)
{
	node.SetAttrib(_T("Outline"),pElem->IsOutline());
	node.SetAttrib(_T("DashStyle"),pElem->GetDashStyle());
	node.SetAttrib(_T("OutlineWidth"),pElem->GetOutlineWidth());
	node.SetAttrib(_T("OutlineColor"),pElem->GetOutlineColor());

	node.SetAttrib(_T("Fill"),pElem->IsFill());
	node.SetAttrib(_T("FillColor"),pElem->GetFillColor());
}

BOOL CXMLVecLS::LoadFilledVecElem(CFilled *pElem,CXmlNode &node)
{
	pElem->SetOutline(node.GetIntAttrib(_T("Outline")));
	pElem->SetDasHStyle(node.GetIntAttrib(_T("DashStyle")));
	pElem->SetOutlineWidth(node.GetIntAttrib(_T("OutlineWidth")));
	pElem->SetOutlineColor(node.GetUIntAttrib(_T("OutlineColor")));
	pElem->SetFill(node.GetIntAttrib(_T("Fill")));
	pElem->SetFillColor(node.GetUIntAttrib(_T("FillColor")));
	return TRUE;
}

void  CXMLVecLS::SaveNonFillVecElem(const COutlined *pElem,CXmlNode &node)
{
	node.SetAttrib(_T("DashStyle"),pElem->GetDashStyle());
	node.SetAttrib(_T("OutlineWidth"),pElem->GetOutlineWidth());
	node.SetAttrib(_T("OutlineColor"),pElem->GetOutlineColor());
}

BOOL CXMLVecLS::LoadNonFillVecElem(COutlined *pElem,CXmlNode &node)
{
	pElem->SetDasHStyle(node.GetIntAttrib(_T("DashStyle")));
	pElem->SetOutlineWidth(node.GetIntAttrib(_T("OutlineWidth")));
	pElem->SetOutlineColor(node.GetUIntAttrib(_T("OutlineColor")));
	return TRUE;
}


#pragma warning(default:4996)

#ifdef TEST_FREE_RETURNNULL
#undef TEST_FREE_RETURNNULL
#endif