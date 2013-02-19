
// PropertyManagerAppDoc.cpp : CPropertyManagerAppDoc 类的实现
//

#include "stdafx.h"
#include "PropertyManagerApp.h"

#include "PropertyManagerAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropertyManagerAppDoc

IMPLEMENT_DYNCREATE(CPropertyManagerAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropertyManagerAppDoc, CDocument)
END_MESSAGE_MAP()


// CPropertyManagerAppDoc 构造/析构

CPropertyManagerAppDoc::CPropertyManagerAppDoc()
{
	// TODO: 在此添加一次性构造代码

}

CPropertyManagerAppDoc::~CPropertyManagerAppDoc()
{
}

BOOL CPropertyManagerAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPropertyManagerAppDoc 序列化

void CPropertyManagerAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPropertyManagerAppDoc 诊断

#ifdef _DEBUG
void CPropertyManagerAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropertyManagerAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPropertyManagerAppDoc 命令
