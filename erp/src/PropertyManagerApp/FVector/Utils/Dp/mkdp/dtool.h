#ifndef __DTOOL_____
#define __DTOOL_____


#define kw_d_struct "_d_struct"
#define kw_d_struct_len (sizeof(kw_d_struct)-1)

#define kw_d_member_id "_d_id"
#define kw_d_memeber_id_len (sizeof(kw_d_member_id)-1)

struct DMemberDesc {
	uint8_t id_;
	uint8_t type_index_;
	std::string name_;
	std::string def_;
	static const uint8_t fixed_id = -1;
};

struct DStructDesc {
	std::string name_;
	std::vector<DMemberDesc> members_;
};

struct DTypeDesc {
	uint8_t id_;
	const char *idName_;
	uint8_t size_;
	const char *sizeName_;
	const char *name_;
	uint8_t nameLen_;
};

void dparse(const char *str,std::vector<DStructDesc> &sts);
std::string dwrite_saver(const DStructDesc &st);
std::string dwrite_loader(const DStructDesc &st);
std::string dwrite_some_saver(const DStructDesc &st);
std::string dwrite_some_loader(const DStructDesc &st);

#endif


