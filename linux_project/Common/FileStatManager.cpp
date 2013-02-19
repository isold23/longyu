#include "FileStatManager.h"


uint8 CFileStatManager::Check ( const char* lszFileName ){
	if( lszFileName != NULL ){
		strncpy( mszFileName, lszFileName, FILE_NAME_LEN );
	}
	if( stat_fn( mszFileName, &moStatus ) == 0 ){
		mbooChecked					=		SUCCEEDED;
		return SUCCEEDED;
	}else{
		mbooChecked					=		FAILED;
		perror( "CFileStatManager::Check stat_fn." );
		return FAILED;
	}
}

uint16 CFileStatManager::GetFileAccessPermission (){
	if( BeChecked() == SUCCEEDED ){
		return moStatus.st_mode & ( S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID
			//#ifndef __BSD_VISIBLE
			//            | S_ISTXT  
			//#endif
			);
	}else {
		return 0;
	}
}

uint8 CFileStatManager::SetFileAccessPermission ( uint16 lu16FileAccessPermission ){
	if( BeChecked() == SUCCEEDED ){
		if( chmod_fn( mszFileName, lu16FileAccessPermission ) == 0 ){
			return SUCCEEDED;
		}else{
			perror( "CFileStatManager::SetFileAccessPermission chmod_fn." );
			return FAILED;
		}
	}else{
		return FAILED;
	}
}

uint8 CFileStatManager::ChangeFileOwner( uid_t uid ){
	if( BeChecked() == SUCCEEDED ){
		if( chown_fn( mszFileName, uid, -1 ) == 0 ){
			return SUCCEEDED;
		}else{
			perror( "CFileStatManager::ChangeFileOwner chown_fn." );
			return FAILED;
		}
	}else{
		return FAILED;
	}
}
