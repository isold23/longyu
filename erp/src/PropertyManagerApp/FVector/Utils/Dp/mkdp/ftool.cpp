#include "tool.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////




uint8_t fTypeOf(const char *s)
{ 
	switch (s[0])
	{
	case 'f':
		return FMemberDesc::Fixed;
	case 'd':
		return FMemberDesc::DStruct;
	case 'a':
		return FMemberDesc::DArray;
	case 's':
		return FMemberDesc::SArray;
	default:
		return FMemberDesc::Non;
	}
}

void fparse(const char *str,std::vector<FStructDesc> &sts)
{
	FStructDesc st;
	FMemberDesc member;

	// struct begin
	char *st_key_start = (char*)str;

	while (st_key_start!=NULL && *st_key_start!='\0')
	{
		// key
		st_key_start = strstr(st_key_start,kw_f_struct);
		if (st_key_start==NULL ||*st_key_start=='\0')  return;

		// struct end
		st_key_start += kw_f_struct_len;	
		st_key_start = skipBlank(st_key_start);
		char *st_key_end= strchr(st_key_start,'}');
		if (st_key_end == NULL) return;

		// struct name
		char *st_name_start = skipBlank(st_key_start);
		if (*st_name_start == '\0') return ;
		st.name_.assign(st_name_start,skipWord(st_name_start));

		bool normal_member_end = false;
		char *member_type_start = strstr(st_name_start,kw_f);
		if (member_type_start == NULL) return;

		while (member_type_start!=NULL && member_type_start<st_key_end)
		{
			// type
			member_type_start += kw_f_len;
			member.type_ = fTypeOf(member_type_start);

			char *member_end = strchr(member_type_start,';');
			if (member_end == NULL) return;

			// def
			char *member_default_key_start = strstr(member_type_start,kw_default);
			if (member_default_key_start >= member_end) member_default_key_start = NULL;
			if (member_default_key_start == NULL) 
			{
				member.def_.clear();
			}
			else
			{
				char *member_default_start = strchr(member_default_key_start+kw_default_len,'(');
				if (member_default_start == NULL) return;

				char *member_default_end = strchr(member_default_start,')');
				member.def_.assign(member_default_start+1,member_default_end);
			}

			// name 
			char *member_name_end = (member_default_key_start!=NULL ? member_default_key_start:member_end);
			while (isblank(*--member_name_end));
			++member_name_end;
			char *member_name_start = member_name_end;
			while (!isblank(*--member_name_start));
			++member_name_start;
			member.name_.assign(member_name_start,member_name_end);

			st.members_.push_back(member);
			member_type_start = strstr(member_name_end,kw_f);
		} 

		sts.push_back(st);
		st.members_.clear();
		st_key_start = st_key_end;
	}

}


std::string fwrite_saver(const FStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// void struct::save(Dp::Writer &w)
	ss << "void " << st.name_ << "::save(Dp::Writer &w)\n";										 
	ss << "{\n";															

	//// Dp::SizeType start = w.cursor();
	//ss << "\tDp::SizeType start = w.cursor();\n";					

	//// w.skip(sizeof(Dp::SizeType));
	//ss << "\tw.skip(sizeof(Dp::SizeType));\n\n";														 

	for (size_t j = 0; j<st.members_.size(); ++j)
	{
		const FMemberDesc &m = st.members_[j];
		ss << "\t//----- " << m.name_ << " -----\n";

		switch (m.type_)
		{
		case FMemberDesc::Fixed:
			// w << xx << ";\n";
			ss << "\tw << " << m.name_ << ";\n";
			break;

		case FMemberDesc::DArray:
			// save_some(w,xx);
			ss << "\tsave_some(w," << m.name_ << ");\n";
			break;

		case FMemberDesc::SArray:
			// raw_save_some(w,xx);
			ss << "\traw_save_some(w," << m.name_ << ");\n";
			break;

		case FMemberDesc::DStruct:
			// xx.save(w);
			ss << "\t " << m.name_ << ".save(w);\n";
			break;
		}

	}

	//// Dp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);
	//ss << "\n\tDp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);\n";

	//// w.set(start,&len,sizeof(Dp::SizeType));
	//ss << "\tw.set(start,&len,sizeof(Dp::SizeType));\n";

	ss << "}\n\n\n";																				

	ss.flush();
	return ss.str();
}

std::string fwrite_loader(const FStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// bool struct::load(Dp::Reader &r)
	ss << "bool " << st.name_ << "::load(Dp::Reader &r)\n";					 
	ss << "{\n";							

	//// Dp::SizeType structLen;  r >> structLen;
	//ss << "\tDp::SizeType structLen;  r >> structLen;\n";							 

	//// Dp::SizeType structEnd = r.cursor() + structLen;
	//ss << "\tDp::SizeType structEnd = r.cursor() + structLen;";						
	//ss << "\n\n";			

	size_t j = 0;
	for (; j<st.members_.size(); ++j)
	{
		const FMemberDesc &m = st.members_[j];

		ss << "\t//----- " << m.name_ << " -----\n";

		switch (m.type_)
		{
		case FMemberDesc::Fixed:
			// r >>  xx;
			ss << "\tr >> " << m.name_ << ";\n";	
			break;

		case FMemberDesc::DArray:
			// load_some(r,xx);
			ss << "\tload_some(r," << m.name_ << ");\n";
			break;

		case FMemberDesc::SArray:
			// raw_load_some(r,xx);
			ss << "\traw_load_some(r," << m.name_ << ");\n";
			break;

		case FMemberDesc::DStruct:
			// xx.load(w);
			ss << "\t " << m.name_ << ".load(r);\n";
			break;
		}
	}

	// return r.ok();
	ss << "\treturn r.ok();\n}\n\n";
	ss.flush();
	return ss.str();
}

