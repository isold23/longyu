#include "tool.h"


DTypeDesc d_type_descs[] = 
{
	{ id_s(Dp::TypesEnum::tid_int8),		id_s(Dp::TypesEnum::size_8),		s_l(int8_t)				},
	{ id_s(Dp::TypesEnum::tid_uint8),		id_s(Dp::TypesEnum::size_8),		s_l(uint8_t)			},
	{ id_s(Dp::TypesEnum::tid_int16),		id_s(Dp::TypesEnum::size_16),		s_l(int16_t)			},
	{ id_s(Dp::TypesEnum::tid_uint16),		id_s(Dp::TypesEnum::size_16),		s_l(uint16_t)			},
	{ id_s(Dp::TypesEnum::tid_int32),		id_s(Dp::TypesEnum::size_32),		s_l(int32_t)			},
	{ id_s(Dp::TypesEnum::tid_uint32),		id_s(Dp::TypesEnum::size_32),		s_l(uint32_t)			},
	{ id_s(Dp::TypesEnum::tid_float),		id_s(Dp::TypesEnum::size_32),		s_l(float)				},
	{ id_s(Dp::TypesEnum::tid_int64),		id_s(Dp::TypesEnum::size_64),		s_l(int64_t)			},
	{ id_s(Dp::TypesEnum::tid_uint64),		id_s(Dp::TypesEnum::size_64),		s_l(uint64_t)			},
	{ id_s(Dp::TypesEnum::tid_double),		id_s(Dp::TypesEnum::size_64),		s_l(double)				},
	{ id_s(Dp::TypesEnum::tid_array),		id_s(Dp::TypesEnum::size_array),	s_l(Dp::Array)			},
	{ id_s(Dp::TypesEnum::tid_buffer),		id_s(Dp::TypesEnum::size_array),	s_l(Dp::Buffer)			},
	{ id_s(Dp::TypesEnum::tid_string),		id_s(Dp::TypesEnum::size_array),	s_l(Dp::String)			},
	{ id_s(Dp::TypesEnum::tid_wstring),		id_s(Dp::TypesEnum::size_array),	s_l(Dp::WString)		},
	{ id_s(Dp::TypesEnum::tid_stdstr),		id_s(Dp::TypesEnum::size_array),	s_l(std::string)		},
	{ id_s(Dp::TypesEnum::tid_stdwstr),		id_s(Dp::TypesEnum::size_array),	s_l(std::wstring)		},
};




uint8_t dTypeIndexOf(const char *s)
{
	for (uint8_t i=0; i<=_countof(d_type_descs); ++i)
	{
		DTypeDesc &d = d_type_descs[i];
		if (strncmp(s,d.name_,d.nameLen_) == 0)
			return i;
	}

	return -1;
}





void dparse(const char *str,std::vector<DStructDesc> &sts)
{ 
	DStructDesc st;
	DMemberDesc member;

	// struct begin
	char *st_key_start = (char*)str;

	while (st_key_start!=NULL && *st_key_start!='\0')
	{
		// key
		st_key_start = strstr(st_key_start,kw_d_struct);
		if (st_key_start==NULL ||*st_key_start=='\0')  return;

		// struct end
		st_key_start += kw_d_struct_len;	
		st_key_start = skipBlank(st_key_start);
		char *st_key_end= strchr(st_key_start,'}');
		if (st_key_end == NULL) return;

		// struct name
		char *st_name_start = skipBlank(st_key_start);
		if (*st_name_start == '\0') return ;
		st.name_.assign(st_name_start,skipWord(st_name_start));

		bool normal_member_end = false;
		char *member_id_start = strstr(st_name_start,kw_d_member_id);
		if (member_id_start == NULL) return;

		while (member_id_start!=NULL && member_id_start<st_key_end)
		{
			// id
			member_id_start += kw_d_memeber_id_len;
			member_id_start = strchr(member_id_start,'(');
			if (member_id_start == NULL) return;

			char *member_end = strchr(member_id_start,';');
			if (member_end == NULL) return;

			member_id_start = skipBlank(++member_id_start);
			member.id_ = isNumerical(*member_id_start) ? atoi(member_id_start) : DMemberDesc::fixed_id;

			if (normal_member_end && member.id_==DMemberDesc::fixed_id ) return;
			if (!normal_member_end && member.id_!= DMemberDesc::fixed_id ) normal_member_end = true;

			// type
			char *member_type_start = strchr(member_id_start,')');
			if (member_type_start++ == NULL) return;

			member_type_start = skipBlank(member_type_start);
			member.type_index_ = dTypeIndexOf(member_type_start);

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
			member_id_start = strstr(member_name_end,kw_d_member_id);
		} 

		sts.push_back(st);
		st.members_.clear();
		st_key_start = st_key_end;
	}
}



std::string dwrite_saver(const DStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// void struct::save(Dp::Writer &w)
	ss << "void " << st.name_ << "::save(Dp::Writer &w)\n";										 
	ss << "{\n";															

	// Dp::SizeType start = w.cursor();
	ss << "\tDp::SizeType start = w.cursor();\n";					

	// w.skip(sizeof(Dp::SizeType));
	ss << "\tw.skip(sizeof(Dp::SizeType));\n\n";														 

	size_t j = 0;
	for (; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];
		if (m.id_ != DMemberDesc::fixed_id)
			break;

		ss << "\t//----- " << m.name_ << " -----\n";
		// w <<  id;
		ss << "\tw << " << m.name_ << ";\n";	
	}

	for (; j<st.members_.size(); ++j)													
	{
		const DMemberDesc &m = st.members_[j]; 

		// ----- m.name_ -----
		ss << "\t//----- " << m.name_ << " -----\n";
	 
		if (d_type_descs[m.type_index_].size_ == Dp::TypesEnum::size_array)
		{
			// if (elem.member.size() != 0)
			ss << "\tif (!" << m.name_ << ".empty())\n\t"; 
		}
		else if (!m.def_.empty())
		{
			// if (elem.member != m.def_)
			ss << "\tif (" << m.name_ << " != " << m.def_ << ")\n\t"; 
		}
		// w << Dp::makeMemberFlag(memberId,type_index); w <<  id;
		ss << "\tw << Dp::makeMemberFlag(" << (int)st.members_[j].id_ << ',' << d_type_descs[m.type_index_].sizeName_; 
		ss<< ") << " << m.name_ << ";\n";	
	}
	

	// Dp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);
	ss << "\n\tDp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);\n";

	// w.set(start,&len,sizeof(Dp::SizeType));
	ss << "\tw.set(start,&len,sizeof(Dp::SizeType));\n";

	ss << "}\n\n\n";																				

	ss.flush();
	return ss.str();
}

std::string dwrite_loader(const DStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// bool struct::load(Dp::Reader &r)
	ss << "bool " << st.name_ << "::load(Dp::Reader &r)\n";					 
	ss << "{\n";							

	// Dp::SizeType structLen;  r >> structLen;
	ss << "\tDp::SizeType structLen;  r >> structLen;\n";							 

	// Dp::SizeType structEnd = r.cursor() + structLen;
	ss << "\tDp::SizeType structEnd = r.cursor() + structLen;";						
	ss << "\n\n";			

	size_t j = 0;
	for (; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];
		if (m.id_ != DMemberDesc::fixed_id)
			break;

		ss << "\t//----- " << m.name_ << " -----\n";
		// r >>  id;
		ss << "\tr >> " << m.name_ << ";\n";	
	}

	// if (!r.ok()) return false;
	ss << "\tif (!r.ok()) return false;\n\n";

	// while (r.cursor() < structEnd)
	ss << "\twhile (r.cursor() < structEnd)\n";									
	ss << "\t{\n";

	// uint8_t mflag; r >> mflag;
	ss << "\t\tuint8_t mflag; r >> mflag;\n";

	// uint8_t mid = Dp::memberId(mflag);
	ss << "\t\tuint8_t mid = Dp::memberId(mflag);\n";

	// uint8_t msize = Dp::memberSize(mflag);
	ss << "\t\tuint8_t msize = Dp::memberSize(mflag);\n";							
	ss << "\n";																	

	// switch (mid)
	ss << "\t\tswitch (mid)\n";													
	ss << "\t\t{\n";															

	for (; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];

		//-----  id -----
		ss << "\t\t//----- " << m.name_ << " -----\n";

		// case _d_id: r >>  member_name; break;
		ss << "\t\tcase " << (int)m.id_ << ": r >> " << m.name_ << "; break;\n" ;	 																						
	}

	// default:
	ss << "\t\tdefault:\n";

	// switch (msize)
	ss << "\t\t\tswitch (msize)\n\t\t\t{\n";
	// case Dp::TypesEnum::size_8: r.skip(1); break;	
	ss << "\t\t\tcase Dp::TypesEnum::size_8: r.skip(1); break;\n";
	// case Dp::TypesEnum::size_16:r.skip(2); break;
	ss << "\t\t\tcase Dp::TypesEnum::size_16:r.skip(2); break;\n";
	// case Dp::TypesEnum::size_32:r.skip(4); break;
	ss << "\t\t\tcase Dp::TypesEnum::size_32:r.skip(4); break;\n";
	// case Dp::TypesEnum::size_64:r.skip(8); break;
	ss << "\t\t\tcase Dp::TypesEnum::size_64:r.skip(8); break;\n";
	// case Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;
	ss << "\t\t\tcase Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;\n";
	// default:break;
	ss << "\t\t\tdefault:break;\n\t\t\t}\n";
	// break;
	ss << "\t\t\tbreak;\n\t\t}\n";

	// if (!r.ok()) return false;	
	ss << "\n\t\tif (!r.ok()) return false;\n";

	ss << "\t}\n";
	// return true;
	ss << "\treturn true;\n}\n\n";

	ss.flush();
	return ss.str();
}




std::string dwrite_some_saver(const DStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// template <Dp::SizeType _Sz> 
	// void save_some(Dp::Writer &w,Dp::Array<Person,_Sz> &elems) {
	// w << elems.size();
	ss << "template <uint32_t _Sz>\n";
	ss << "void save_some(Dp::Writer &w,const Dp::Array<" << st.name_ << ",_Sz> &elems) \n{\n\t";
	ss << "w << elems.size();\n\n";

	size_t i;
	size_t fixedCount = 0;
	for (; st.members_[fixedCount].id_==DMemberDesc::fixed_id; ++fixedCount);

	// const uint8_t flags = {,,,};
	if (fixedCount != st.members_.size())
	{
		ss << "\tconst uint8_t flags[] = {\n";

		for (i=fixedCount; i<st.members_.size()-1; ++i)
			ss << "\t\t\tDp::makeMemberFlag(" << (int)st.members_[i].id_ << ",\t" << d_type_descs[st.members_[i].type_index_].sizeName_ << "),\n";

		ss << "\t\t\tDp::makeMemberFlag(" << (int)st.members_[i].id_ << ",\t" << d_type_descs[st.members_[i].type_index_].sizeName_ << ")\n\t\t};\n";
	}

	// w << (Dp::SizeType)0;
	// w << (Dp::SizeType)sizeof(flags);  w.put(flags,sizeof(flags));
	if (fixedCount == st.members_.size())
		ss << "\tw << (Dp::SizeType)0;\n\n";
	else
		ss << "\tw << (Dp::SizeType)sizeof(flags);  w.put(flags,sizeof(flags));\n\n";

	// for (size_t i=0; i<elems.size(); ++i) {
	ss << "\tfor (size_t i=0; i<elems.size(); ++i)\n\t{\n\t\t";
	// const Person &elem = elems[i];
	ss << "const " << st.name_ <<" &elem = elems[i];\n\n\t\t";
	// Dp::SizeType start = w.cursor();
	ss << "Dp::SizeType start = w.cursor();\n\t\t";
	// w.skip(sizeof(Dp::SizeType));
	ss << "w.skip(sizeof(Dp::SizeType));\n\n";

	for (size_t j=0; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];
		ss << "\t\t//----- elem." << m.name_ << " -----\n";
		ss << "\t\tw << elem." << m.name_ << ";\n";
	}

	// Dp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);
	ss << "\t\tDp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);\n";
	// w.set(start,len);
	ss << "\t\tw.set(start,len);\n\t}\n}\n\n";

	ss.flush();
	return ss.str();
}

std::string dwrite_some_loader(const DStructDesc &st)
{
	std::stringstream ss(std::ios::out);

	// template <Dp::SizeType _Sz>
	// bool load_some(Dp::Reader &r,Dp::Array<Person,_Sz> &elems) {
	ss << "template <Dp::SizeType _Sz>\n";
	ss << "bool load_some(Dp::Reader &r,Dp::Array<" << st.name_ << ",_Sz> &elems) \n{\n\t";

	// Dp::SizeType count; r >> count;
	ss << "Dp::SizeType count; r >> count;\n\t";
	// Dp::Array<uint8_t,32> flags; r >> flags;
	ss << "Dp::Array<uint8_t,32> flags; r >> flags;\n\n\t";

	// for (Dp::SizeType i=0; i<count; ++i) {
	ss << "for (Dp::SizeType i=0; i<count; ++i)\n\t{\n\t\t";

	// Person elem;
	ss << st.name_ <<" elem;\n\n";

	// Dp::SizeType structLen; r >> structLen;
	ss << "\t\tDp::SizeType structLen; r >> structLen;\n";
	// Dp::SizeType structEnd = r.cursor() + structLen;
	ss << "\t\tDp::SizeType structEnd = r.cursor() + structLen;\n\n";		

	size_t j = 0;
	for (; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];
		if (m.id_ != DMemberDesc::fixed_id)
			break;

		ss << "\t\t//----- " << m.name_ << " -----\n";
		// r >>  id;
		ss << "\t\tr >> elem." << m.name_ << ";\n";	
	}
	// if (!r.ok()) return false;
	ss << "\t\tif (!r.ok()) return false;\n\n\t\t";

	// for (Dp::SizeType j=0; j<flags.size(); ++j)
	ss << "for (Dp::SizeType j=0; j<flags.size(); ++j) \n\t\t{\n\t\t\t";

	// uint8_t mid = Dp::memberId(flags[j]);
	ss << "uint8_t mid = Dp::memberId(flags[j]);\n\t\t\t";
	// uint8_t msize  = Dp::memberSize((flags[j]));
	ss << "uint8_t msize  = Dp::memberSize((flags[j]));\n\n\t\t\t";

	// switch (mid)
	ss << "switch (mid)\n";													
	ss << "\t\t\t{\n";	

	for (j=0; j<st.members_.size(); ++j)
	{
		const DMemberDesc &m = st.members_[j];
		if (m.id_ == DMemberDesc::fixed_id)
			continue;

		//-----  id -----
		ss << "\t\t\t//----- " << m.name_ << " -----\n";

		// case _d_id: r >>  member_name; break;
		ss << "\t\t\tcase " << (int)m.id_ << ": r >> elem." << m.name_ << "; break;\n" ;	 																						
	}

	// default:
	ss << "\t\t\tdefault:\n";

	// switch (msize)
	ss << "\t\t\t\tswitch (msize)\n\t\t\t\t{\n";
	// case Dp::TypesEnum::size_8: r.skip(1); break;	
	ss << "\t\t\t\tcase Dp::TypesEnum::size_8: r.skip(1); break;\n";
	// case Dp::TypesEnum::size_16:r.skip(2); break;
	ss << "\t\t\t\tcase Dp::TypesEnum::size_16:r.skip(2); break;\n";
	// case Dp::TypesEnum::size_32:r.skip(4); break;
	ss << "\t\t\t\tcase Dp::TypesEnum::size_32:r.skip(4); break;\n";
	// case Dp::TypesEnum::size_64:r.skip(8); break;
	ss << "\t\t\t\tcase Dp::TypesEnum::size_64:r.skip(8); break;\n";
	// case Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;
	ss << "\t\t\t\tcase Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;\n";
	// default:break;
	ss << "\t\t\t\tdefault:break;\n\t\t\t\t}\n";
	// break;
	ss << "\t\t\t\tbreak;\n\t\t\t}\n\t\t}\n";

	// if (!r.ok()) return false;	
	ss << "\n\t\tif (!r.ok() || r.cursor()!=structEnd) \n\t\t\treturn false;\n";

	// elems.push_back(elem);
	ss << "\t\telems.push_back(elem);\n";

	ss << "\t}\n";

	// return true;
	ss << "\treturn true;";
	ss << "\n}\n";

	ss.flush();
	return ss.str();
}
