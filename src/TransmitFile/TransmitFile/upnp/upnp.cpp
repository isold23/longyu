#include "stdafx.h"
#include "upnp.h"

CUpnpNat::CUpnpNat()
:m_sPort(13800)
{
	AddPortMapping();
}

CUpnpNat::~CUpnpNat()
{
	DelPortMapping();
}
int CUpnpNat::AddPortMapping()
{
	UPNPNAT nat;
	strstream strError;
	nat.init(5,5);
	if(!nat.discovery())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.get_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.parser_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;	
	}

	if(nat.add_port_mapping(m_sPort,"UDP"))
	{
		strError<<"³É¹¦Ìí¼Ó¶Ë¿ÚÓ³Éä UDP port = "<<m_sPort<<endl<<ends;
		ATLTRACE(strError.str());
		return 1;
	}
	else
	{
		strError<<"Ìí¼Ó¶Ë¿ÚÓ³ÉäÊ§°Ü UDP: "<<m_sPort<<" ´íÎó£º"<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}
}

int CUpnpNat::DelPortMapping()
{
	UPNPNAT nat;
	strstream strError;
	nat.init(5,5);
	if(!nat.discovery())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.get_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.parser_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;	
	}

	if(nat.del_port_mapping(m_sPort,"UDP"))
	{
		strError<<"³É¹¦É¾³ý¶Ë¿ÚÓ³Éä UDP"<<endl<<ends;
		ATLTRACE(strError.str());
		return 1;
	}
	else
	{
		strError<<"É¾³ý¶Ë¿ÚÓ³ÉäÊ§°Ü UDP: "<<m_sPort<<" ´íÎó£º"<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}
}