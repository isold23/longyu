#include "StdAfx.h"
#include "ObjectDesc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
tagOpDesc::tagOpDesc(void) 
{  
}

tagOpDesc::tagOpDesc(FieldsPtr &fields)
{
	_variant_t varId = fields->Item[L"OpId"]->Value;
	if (varId.vt==VT_NULL || varId.vt==VT_EMPTY)
	{
		Id = -1;
	}
	else
	{ 
		Id =  varId;
		Name =  fields->Item[L"OpName"]->Value;
		Intro =  fields->Item[L"OpIntro"]->Value;
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

tagGroupDesc g_group;

tagGroupDesc::tagGroupDesc(void)
{

}

tagGroupDesc::tagGroupDesc(int nGroupId,FieldsPtr &fields) 
{ 
	Id = nGroupId;
	Name = fields->Item[L"GroupName"]->Value;
	Intro = fields->Item[L"GroupIntro"]->Value;
	ParentId = fields->Item[L"GroupParent"]->Value;
}

tagGroupDesc::~tagGroupDesc(void)
{
	Clear();
}


int tagGroupDesc::FromUserId(UINT nUserId,CString &strErrDesc)
{ 
	Clear();

	_RecordsetPtr rst;
	int nRet = g_sp.RRGetGroupOps(rst,nUserId,strErrDesc);
	if (nRet >= 0) 
	{

		CArray<tagGroupDesc*,tagGroupDesc*> groups;
		GroupsFromRecordset(groups,rst);
 
		for (INT_PTR i=0; i<groups.GetCount(); ++i)
			BuildRelation(groups[i]);
		ASSERT(Childs.GetCount() == 1);
	}

	return nRet;
}

void tagGroupDesc::ToGroups(CArray<tagGroupDesc*,tagGroupDesc*> &groups)
{
	for (INT_PTR i=0; i<Childs.GetCount(); ++i)
	{
		groups.Add(Childs[i]);
		Childs[i]->ToGroups(groups);
	}	 
}

void tagGroupDesc::Clear(void)
{
	for (INT_PTR i=0; i<Childs.GetCount(); ++i)
		delete Childs[i];
	Childs.RemoveAll();
	Ops.RemoveAll();
}


void tagGroupDesc::GroupsFromRecordset(CArray<tagGroupDesc*,tagGroupDesc*> &groups, _RecordsetPtr &rst)
{
	if (rst == NULL) return ;

	while (!rst->adoEOF)
	{
		tagGroupDesc * pGroup = NULL;
		FieldsPtr fields = rst->Fields;
		int nGroupId = fields->Item[L"GroupId"]->Value;

		INT_PTR i = 0;
		for (; i<groups.GetCount() && groups[i]->Id!=nGroupId; ++i);

		if (i != groups.GetCount())
		{
			pGroup = groups[i];
		}
		else
		{
			pGroup = new tagGroupDesc(nGroupId,fields); 
			groups.Add(pGroup);
		} 
		tagOpDesc op(fields); 
		if (op.IsValid())
		{
			op.Group = pGroup;
			pGroup->Ops.Add(op);
		}

		rst->MoveNext();
	}
}

tagGroupDesc* tagGroupDesc::HasChild(tagGroupDesc *child)
{
	if (child->ParentId == Id)
		return this;

	for (INT_PTR i=0; i<Childs.GetCount(); ++i)
	{
		tagGroupDesc *g = Childs[i]->HasChild(child);
		if (g != NULL)
			return g;
	}
	return NULL;
}



int tagGroupDesc::BuildRelation(tagGroupDesc *src)
{ 
	BOOL bSrcProcessed = FALSE;
	for (INT_PTR i=0; i<Childs.GetCount(); )
	{
		tagGroupDesc *c = Childs[i];
		tagGroupDesc *g = c->HasChild(src);
		if (g != NULL)
		{
			src->pParent = g;
			g->Childs.Add(src);

			ASSERT(!bSrcProcessed); 
			bSrcProcessed = TRUE;

			++i;
		}
		else if (c->ParentId == src->Id)
		{
			src->Childs.Add(c);
			c->pParent = src;
			Childs.RemoveAt(i);
		}
		else
		{
			++i;
		}
	}

	if (!bSrcProcessed)
		Childs.Add(src);

	return 0;
}
 

 