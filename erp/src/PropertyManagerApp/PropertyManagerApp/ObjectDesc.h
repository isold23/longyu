#pragma once
#include "Sql/sql.h"

struct tagGroupDesc;

//////////////////////////////////////////////////////////////////////////
struct tagOpDesc 
{
	tagOpDesc(void);
	tagOpDesc(FieldsPtr &fields);
	BOOL IsValid(void) const;

	int Id;
	CString Name;
	CString Intro;
	tagGroupDesc *Group;
};

inline BOOL tagOpDesc::IsValid(void) const {
	return Id != -1;
}
//////////////////////////////////////////////////////////////////////////

struct tagGroupDesc 
{
	tagGroupDesc(void);
	tagGroupDesc(int nGroupId,FieldsPtr &fields);
	~tagGroupDesc(void);

	int FromUserId(UINT nUserId,CString &strErrDesc);
	void ToGroups(CArray<tagGroupDesc*,tagGroupDesc*> &groups);

	int		Id;
	CString Name;
	CString Intro;
	int		ParentId;

	tagGroupDesc *pParent;
	CArray<tagOpDesc,tagOpDesc&> Ops;
	CArray<tagGroupDesc*,tagGroupDesc*> Childs;

private:
	void Clear(void);

	int BuildRelation(tagGroupDesc *src);
	tagGroupDesc* HasChild(tagGroupDesc *child);
	void GroupsFromRecordset(CArray<tagGroupDesc*,tagGroupDesc*> &groups, _RecordsetPtr &rst);
};



extern tagGroupDesc g_group;

