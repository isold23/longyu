#include "Time.h"

uint64 CTimeBase::get_current_time()
{
	struct timeb loTimeb;
	memset(&loTimeb, 0 , sizeof(timeb));
	ftime(&loTimeb); 
	return ((uint64)loTimeb.time * 1000) + loTimeb.millitm;
}

uint64 CTimeBase::escape_time(uint64 last_time)
{
	return 0;
}

string CTimeBase::get_now()
{
	string strCurrentTime = "";

	struct timeb loSystemTime;
	ftime(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime.time);
	
	stringstream lstrTimeNow;
	lstrTimeNow.fill('0');
	lstrTimeNow<<setw(4)<<1900+lptm->tm_year<<"-"<<
		setw(2)<<1+lptm->tm_mon<<"-"<<
		setw(2)<<lptm->tm_mday<<" "<<
		setw(2)<<lptm->tm_hour<<":"<<
		setw(2)<<lptm->tm_min<<":"<<
		setw(2)<<lptm->tm_sec<<":"<<
		setw(3)<<loSystemTime.millitm<<ends;

	strCurrentTime = lstrTimeNow.str();

	return strCurrentTime;
}