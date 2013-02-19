#ifndef __F__D__TOOL__
#define __F__D__TOOL__

 
#define kw_fd_struct "_fd_struct"

#define kw_fd_member_prefix "_d_"
#define kw_fd_member_f "_d_f"	// fixed load	---		>>/<<
#define kw_fd_member_a "_d_a"	// array load	---		load_some/save_some
#define kw_fd_member_i "_d_i"	// id load		---		load/save

struct DFMemberDesc {
	uint8_t id_;
	uint8_t type_index_;
	std::string name_;
	std::string def_;
	static const uint8_t fixed_index = -1;
	static const uint8_t array_index = -2;

};

struct DFStructDesc {
	std::string name_;
	std::vector<DFMemberDesc> members_;
};

struct DFTypeDesc {
	uint8_t id_;
	const char *idName_;
	uint8_t size_;
	const char *sizeName_;
	const char *name_;
	uint8_t nameLen_;
};

void dfparse(const char *str,std::vector<DStructDesc> &sts);
std::string dfwrite_saver(const DStructDesc &st);
std::string dfwrite_loader(const DStructDesc &st);
std::string dfwrite_some_saver(const DStructDesc &st);
std::string dfwrite_some_loader(const DStructDesc &st);




#endif
