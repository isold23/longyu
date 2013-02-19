#ifndef __FTOOL_____
#define __FTOOL_____


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define kw_f "_f_"
#define kw_f_len (sizeof(kw_f)-1)

#define kw_f_struct "_f_struct"
#define kw_f_struct_len (sizeof(kw_f_struct)-1)

//#define kw_f_f_member "_f_f"
//#define kw_f_f_memeber_len (sizeof(kw_f_f_member)-1)
//
//#define kw_f_d_member "_f_d"
//#define kw_f_d_member_len (sizeof(kw_f_d_member)-1)
//
//#define kw_f_a_member "_f_a"
//#define kw_f_a_member_len (sizeof(kw_f_a_member)-1)


struct FMemberDesc {
	enum FType {Non, Fixed,DStruct,DArray,SArray };

	uint8_t type_;
	std::string name_;
	std::string def_;
};

struct FStructDesc {
	std::string name_;
	std::vector<FMemberDesc> members_;
};

void fparse(const char *str,std::vector<FStructDesc> &sts);
std::string fwrite_saver(const FStructDesc &st);
std::string fwrite_loader(const FStructDesc &st);






#endif
