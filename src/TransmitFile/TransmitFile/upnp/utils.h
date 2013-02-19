/***************************************************************************
 *   Copyright (C) 2006 by taofei   *
 *   gudu2005@126.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

	
inline bool parseUrl(const char* url,std::string& host,unsigned short* port,std::string& path)
{
	std::string str_url=url;
	
	std::string::size_type pos1,pos2,pos3;
	pos1=str_url.find("://");
	if(pos1==std::string::npos)
	{
		return false;
	}
	pos1=pos1+3;


	pos2=str_url.find(":",pos1);
	if(pos2==std::string::npos)
	{
		*port=80;
		pos3=str_url.find("/",pos1);
		if(pos3==std::string::npos)
		{
			return false;
		}
		
		host=str_url.substr(pos1,pos3-pos1);

	}
	else
	{
		
		host=str_url.substr(pos1,pos2-pos1);
		pos3=str_url.find("/",pos1);
		if(pos3==std::string::npos)
		{
			return false;
		}
		
		std::string str_port=str_url.substr(pos2+1,pos3-pos2-1);
		*port=(unsigned short)atoi(str_port.c_str());
	}
	
	if(pos3+1>=str_url.size())
	{
		path="/";
	}
	else
	{

		path=str_url.substr(pos3,str_url.size());
	}	

	return true;
}
