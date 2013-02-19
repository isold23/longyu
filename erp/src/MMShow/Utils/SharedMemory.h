#ifndef _SHARED_MEMORY_
#define _SHARED_MEMORY_
#include <windows.h> 

//////////////////////////////////////////////////////////////////////////
/////////////////////////////StreamMemory/////////////////////////////////
//////////////////////////////////////////////////////////////////////////
template<class _Mty>
class SharedMemory
{
	static const int MERMORY_SIZE = sizeof(_Mty);

public:
	SharedMemory(void)
		:file_(NULL),
		 event_(NULL),
		 data_(NULL) {
	}

	~SharedMemory(void) {
		if (file_ != NULL)
			free();
	}

	_Mty* data(void) {
		return data_;
	}

	const _Mty* data(void) const {
		return data_;
	}

	int init(LPCWSTR name,BOOL producer) {
		
		WCHAR fileName[MAX_PATH];
		wsprintfW(fileName,L"file_%s",name);

		WCHAR eventName[MAX_PATH];
		wsprintfW(eventName,L"event_%s",name);

		int ret = 0;
		if (file_ == NULL) {
			file_ = ::CreateFileMappingW(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(_Mty),fileName);
			if (file_!=NULL && file_!=INVALID_HANDLE_VALUE)  {
				event_ = ::CreateEvent(NULL,TRUE,FALSE,eventName);
				ret = 1;
			}
			else {
				if (::GetLastError() != ERROR_ALREADY_EXISTS)
					return 0;

				file_ = ::OpenFileMappingW(FILE_MAP_ALL_ACCESS,FALSE,fileName); 
				if (file_==NULL || file_==INVALID_HANDLE_VALUE)
					return 0;
				event_ = ::OpenEvent(EVENT_ALL_ACCESS,FALSE,eventName);
				ret = -1;
			}

			DWORD access = producer ? FILE_MAP_WRITE : FILE_MAP_READ;
			data_ = (_Mty*)::MapViewOfFile(file_,access,0,0,sizeof(_Mty));
		}
 
		return ret;
	}

	BOOL free(void) {
		if (file_ == NULL) {
			return FALSE;
		}
		else { 
			::UnmapViewOfFile(data_);
			data_ = NULL;
			::CloseHandle(file_);
			file_ = NULL;
			::CloseHandle(event_);
			event_ = NULL;
			return TRUE;
		}
	}

	HANDLE event(void) {
		return event_;
	}

	void notify(void) {
		::SetEvent(event_);
		::ResetEvent(event_);
	}

private:
	_Mty *data_; 
	HANDLE event_;
	HANDLE file_;
};

#include "MediaType.h"


struct VideoMemoryData
{
public: 
	DWORD time;
	BYTE frame[MediaType::VIDEO_FSIZE];
};


struct AudioMemoryData
{
public: 
	DWORD time;
	DWORD curFrame;
	BYTE frame[MediaType::AUDIO_FPS][MediaType::AUDIO_FSIZE];
};


typedef SharedMemory<VideoMemoryData> VideoMemory;
typedef SharedMemory<AudioMemoryData> AudioMemory;


#endif
