#include "stdafx.h"
#include  "BinVecLS.h"
#include "../ElemInc.h" 
  
BOOL CBinVecLS::Load(LPCTSTR pcszFileName,stVecParam &param,CElems &elems)
{
	HANDLE hFile = ::CreateFile(pcszFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwRead;
	DWORD dwFileSize = ::GetFileSize(hFile,NULL);
	char *buffer = new char[dwFileSize];
	DWORD_PTR dwEndPos = reinterpret_cast<DWORD_PTR>(buffer) + dwFileSize;
	ReadFile(hFile,buffer,dwFileSize,&dwRead,NULL);
	ASSERT(dwRead == dwFileSize);


	Dp::Reader r(buffer,dwRead);
	CElem *pElem;
 
	Dp::Buffer<TCHAR> tmpBuf;
	r >> tmpBuf;
	param.strBkgndImage = CString(tmpBuf.ptr(),tmpBuf.size());
	r >> param.clrBk;
	r >> param.dwCustomData;
	r >> tmpBuf;
	param.strDesc = CString(tmpBuf.ptr(),tmpBuf.size());

	r >> param.scale;
	BOOL err = FALSE;
	while (r.ok() && !err)
	{
		pElem = LoadElem(r);
		if (pElem == NULL)
			err = TRUE;
		else
			elems.Add(pElem);	 
	}
	
	delete[] buffer;	
	::CloseHandle(hFile);

	if (!err && r.ok())
		return TRUE;

	for (int i=0; i<elems.GetCount(); ++i)
		delete elems[i];
	elems.RemoveAll();
	return FALSE;
}

BOOL CBinVecLS::Save(LPCTSTR pcszFileName,const stVecParam &param,const CElems &elems)
{
	HANDLE hFile = ::CreateFile(pcszFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	Dp::Writer w;
	w << Dp::make_buffer(param.strBkgndImage.GetString(),param.strBkgndImage.GetLength());
	w << param.clrBk;
	w << Dp::make_buffer(param.strDesc.GetString(),param.strDesc.GetLength());
	w << param.scale;
	w << param.dwCustomData;
	for (int i=0; i<elems.GetCount(); ++i)
		SaveElem(elems[i],w);	

	DWORD dwWrite;
	::WriteFile(hFile,w.ptr(),w.size(),&dwWrite,NULL);

	::CloseHandle(hFile);
	return TRUE;
}


template <class WRITER>
void CBinVecLS::SaveElem(const CElem *pElem,WRITER &w)
{
	CRectF rc;

	int nType = pElem->GetType();
	w.put(nType);
	w.put(pElem->GetCustomData());
	w << Dp::make_buffer(pElem->GetDesc().GetString(),pElem->GetDesc().GetLength());
	//w << pElem->GetTextColor();
	//w << Dp::make_buffer(pElem->GetText().GetString(),pElem->GetText().GetLength());
	switch (nType)
	{
	case CElem::Line:
		{
			const CLine *elem = static_cast<const CLine*>(pElem);
			SaveNonFillVecElem(elem,w);
			w.put(elem->GetStartPoint());
			w.put(elem->GetEndPoint());
		}
		break;
	case CElem::FreeLine:
		{
			const CFreeLine *elem = static_cast<const CFreeLine*>(pElem);
			SaveNonFillVecElem(elem,w); 
			w.put(Dp::make_buffer(elem->GetPoints().GetData(),(Dp::SizeType)elem->GetPoints().GetCount()));
		}
		break;

	case CElem::Bezier:
		{
			const CBezier *elem = static_cast<const CBezier*>(pElem);	
			SaveNonFillVecElem(elem,w);
			w.put(Dp::make_buffer(elem->GetPoints().GetData(),(Dp::SizeType)elem->GetPoints().GetCount()));
		}
		break;
	case CElem::Arc:
		{
			const CArc *elem = static_cast<const CArc*>(pElem);
			SaveNonFillVecElem(elem,w);
			elem->GetBoundsRect(rc);
			w.put(rc);
			w.put(elem->GetStartAngel());
			w.put(elem->GetEndAngel());
		}
		break;
	case CElem::Poly:
		{
			const CPoly *elem = static_cast<const CPoly*>(pElem);
			SaveVecElem(elem,w);
			w.put(Dp::make_buffer(elem->GetPoints().GetData(),(Dp::SizeType)elem->GetPoints().GetCount()));
		}
		break;
	case CElem::Region:
		{
			const CRegion *elem = static_cast<const CRegion*>(pElem);
			SaveVecElem(elem,w);
			w.put(Dp::make_buffer(elem->GetPoints().GetData(),(Dp::SizeType)elem->GetPoints().GetCount()));
		}
		break;
	case CElem::Rectangle:
		{
			const CRectangle *elem = static_cast<const CRectangle*>(pElem);	
			SaveVecElem(elem,w);
			w << elem->GetTextColor();
			w << Dp::make_buffer(elem->GetText().GetString(),elem->GetText().GetLength());
			elem->GetBoundsRect(rc);
			w.put(rc);
		}
		break;
	case CElem::RoundRect:
		{
			const CRoundRect *elem = static_cast<const CRoundRect*>(pElem);
			SaveVecElem(elem,w);	
			
			elem->GetBoundsRect(rc);
			w.put(rc);
			w.put(elem->GetXEllipse());
			w.put(elem->GetYEllipse());
		}
		break;
	case CElem::Ellipse:
		{
			const CEllipse *elem = static_cast<const CEllipse*>(pElem);
			SaveVecElem(elem,w);
			elem->GetBoundsRect(rc);
			w.put(rc);

		}
		break;
	case CElem::Chord:
		{
			const CChord *elem = static_cast<const CChord*>(pElem);
			SaveVecElem(elem,w);
			
			elem->GetBoundsRect(rc);
			w.put(rc);
			w.put(elem->GetStartAngel());
			w.put(elem->GetEndAngel());
		}
		break;
	case CElem::Pie:
		{
			const CChord *elem = static_cast<const CChord*>(pElem);
			SaveVecElem(elem,w);	
		
			elem->GetBoundsRect(rc);
			w.put(rc);
			w.put(elem->GetStartAngel());
			w.put(elem->GetEndAngel());
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

CElem* CBinVecLS::LoadElem(Dp::Reader &r)
{  
	int nType; 
	r.get(nType); 

	DWORD_PTR dwCustomData;
	Dp::Buffer<TCHAR> desc;
	COLORREF clrText;
	Dp::Buffer<TCHAR> text;
	r >> dwCustomData >> desc >> clrText >> text;
	
	CPointF pt;
	CRectF rc;
	REAL f;

	CElem *elem = NULL;
	switch (nType)
	{
	case CElem::Line:
		{		
			CLine *pElem = new CLine();
			LoadNonFillVecElem(pElem,r);
			
			r.get(pt);
			pElem->SetStartPoint(pt);
			r.get(pt);
			pElem->SetEndPoint(pt);
			elem = pElem;
		}
		break;
	case CElem::Bezier:
		{		
			CBezier *pElem = new CBezier();
			LoadNonFillVecElem(pElem,r);

			int cnt;
			r.get(cnt);

			CFPoints pts;
			pts.SetSize(cnt);
			r.get(reinterpret_cast<LPSTR>(pts.GetData()),cnt*sizeof(POINTF));
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::FreeLine:
		{		
			CFreeLine *pElem = new CFreeLine();
			LoadNonFillVecElem(pElem,r);

			int cnt;
			r.get(cnt);

			CFPoints pts;
			pts.SetSize(cnt);
			r.get(reinterpret_cast<LPSTR>(pts.GetData()),cnt*sizeof(POINTF));
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;
	case CElem::Region:
		{		
			CRegion *pElem = new CRegion();
			LoadVecElem(pElem,r);

			int cnt;
			r.get(cnt);

			CFPoints pts;
			pts.SetSize(cnt);
			r.get(reinterpret_cast<LPSTR>(pts.GetData()),cnt*sizeof(POINTF));
			pElem->SetPoints(pts);
			elem = pElem;
		}
		break;

	case CElem::Arc:
		{
			CArc *pElem = new CArc();
			LoadNonFillVecElem(pElem,r);

			r.get(rc);
			pElem->SetBoundsRect(rc);
			r.get(f);
			pElem->SetStartAngel(f);
			r.get(f);
			pElem->SetEndAngel(f);
			elem = pElem;;
		}
		break;
	case CElem::Poly:
		{
			CPoly *pElem = new CPoly();
			LoadVecElem(pElem,r);

			Dp::Buffer<CPointF> buf;
			r.get(buf);
			CFPoints pts(buf.ptr(),buf.ptr()+buf.size());
			pElem->SetPoints(pts);
			elem = pElem;;
		}
		break;
	case CElem::Rectangle:
		{			
			CRectangle *pElem = new CRectangle();
			LoadVecElem(pElem,r);

			r >> clrText >> text;
			pElem->SetTextColor(clrText);
			pElem->SetText(CString(text.ptr(),text.size()));
			r.get(rc);
			pElem->SetBoundsRect(rc);
			elem = pElem;;
		}
		break;
	case CElem::RoundRect:
		{
			CRoundRect *pElem = new CRoundRect();

			LoadVecElem(pElem,r);
			r.get(rc);
			pElem->SetBoundsRect(rc);
			r.get(f);
			pElem->SetXEllipse(f);
			r.get(f);
			pElem->SetYEllipse(f);
			elem = pElem;;
		}
		break;
	case CElem::Ellipse:
		{
			CEllipse *pElem = new CEllipse();

			LoadVecElem(pElem,r);
			r.get(rc);
			pElem->SetBoundsRect(rc);
			elem = pElem;;
		}
		break;
	case CElem::Chord:
		{
			CChord *pElem = new CChord();

			LoadVecElem(pElem,r);

			r.get(rc);
			pElem->SetBoundsRect(rc);
			r.get(f);
			pElem->SetStartAngel(f);
			r.get(f);
			pElem->SetEndAngel(f);
			elem = pElem;; 
		}
		break;
	case CElem::Pie:
		{
			CPie *pElem = new CPie();

			LoadVecElem(pElem,r);

			r.get(rc);
			pElem->SetBoundsRect(rc);
			r.get(f);
			pElem->SetStartAngel(f);
			r.get(f);
			pElem->SetEndAngel(f);
			elem = pElem;;  
		}
		break;

	default: 
		ASSERT(FALSE);
		break;
	} 

	if (elem != NULL)
	{
		elem->SetCustomData(dwCustomData);
		elem->SetDesc(CString(desc.ptr(),desc.size()));
		//elem->SetTextColor(clrText);
		//elem->SetText(CString(text.ptr(),text.size()));
	}
	return elem;
}

template <class WRITER>
void CBinVecLS::SaveVecElem(const CFilled *pElem,WRITER &w)
{
	w.put(pElem->IsOutline());
	w.put(pElem->GetDashStyle());
	w.put(pElem->GetOutlineWidth());
	w.put(pElem->GetOutlineColor());
	w.put(pElem->IsFill());
	w.put(pElem->GetFillColor());
}


void CBinVecLS::LoadVecElem(CFilled *pElem,Dp::Reader &r)
{
	BOOL bOutline;
	r.get(bOutline);

	int nDashStyle;
	r.get(nDashStyle);

	int nOutlineWidth;
	r.get(nOutlineWidth);

	COLORREF clrOutline;
	r.get(clrOutline);

	pElem->SetOutline(bOutline);
	pElem->SetDasHStyle(nDashStyle);
	pElem->SetOutlineWidth(nOutlineWidth);
	pElem->SetOutlineColor(clrOutline);

	BOOL bFill;
	r.get(bFill);

	COLORREF clrFill;
	r.get(clrFill);

	pElem->SetFill(bFill);
	pElem->SetFillColor(clrFill);
}

template <class WRITER>
void CBinVecLS::SaveNonFillVecElem(const COutlined *pElem,WRITER &w)
{
	w.put(pElem->GetDashStyle());
	w.put(pElem->GetOutlineWidth());
	w.put(pElem->GetOutlineColor());
}


void CBinVecLS::LoadNonFillVecElem(COutlined *pElem,Dp::Reader &r)
{
	int nDashStyle;
	r.get(nDashStyle);

	int nOutlineWidth;
	r.get(nOutlineWidth);

	COLORREF clrOutline;
	r.get(clrOutline);

	pElem->SetDasHStyle(nDashStyle);
	pElem->SetOutlineWidth(nOutlineWidth);
	pElem->SetOutlineColor(clrOutline);
}
