#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_


#include <sys/stat.h>
#include "include.h"
#include "define.h"

#define stat_fn stat
#define lstat_fn lstat
#define fstat_fn fstat
#define chmod_fn chmod
#define fchmod_fn fchmod
#define lchmod_fn lchmod
#define fchmodat_fn fchmodat
#define chown_fn chown

class CFileStatManager{
public:

	CFileStatManager (){
		Reset();
	}

	~CFileStatManager (){
		Reset();
	}

	void		Reset (){
		mbooChecked					=		FAILED;
		memset( &moStatus, 0, sizeof( stat_t ) );
		memset( mszFileName, 0, FILE_NAME_LEN );
	}

	// 功	能：获取指定文件Name的status信息。
	// 参	数：pFileName 指定的文件名。
	// 返	回：成功 SUCCEEDED，失败 FAILED。
	uint8		Check ( const char* pFileName = NULL );

	// 功	能：获取指定文件的类型。
	// 参	数：无
	// 返	回：文件类型
	uint32		GetFileType ();

	// 功	能：获取访问权限。
	// 参	数：无
	// 返	回：访问权限
	uint16		GetFileAccessPermission ();

	// 功	能：设置访问权限。
	// 参	数：访问权限
	// 返	回：成功 SUCCEEDED，失败 FAILED。
	uint8		SetFileAccessPermission ( uint16 );

	// 功	能：修改文件的拥有者账户
	// 参	数：uid 新的账户ID
	// 返	回：成功 SUCCEEDED，失败 FAILED。
	uint8		ChangeFileOwner ( uid_t uid );

private:
	// 功	能：指定文件是否获取成功
	// 参	数：无
	// 返	回：成功 SUCCEEDED，失败 FAILED。
	uint8		BeChecked (){
		return mbooChecked;
	}
	
private:
	typedef struct stat		stat_t;
	static const int		FILE_NAME_LEN = 255;
	char					mszFileName[ FILE_NAME_LEN ];
	stat_t					moStatus;
	uint8					mbooChecked;
};

#endif // _FILEMANAGER_H_

