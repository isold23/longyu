#include "DCSDealData.h"
#include "dcs_dns.h"
CDCSDealData::CDCSDealData()
{

}

CDCSDealData::~CDCSDealData()
{

}
uint32 CDCSDealData::DCSDealData(const char *apIn, 
				   const uint32 aiIn, char *apOut, uint32 &aiOut)
{
	char original_data[DCS_DNS_BUFFER_LEN] = {0};
	char pack_data[DCS_DNS_BUFFER_LEN] = {0};
	uint16 original_lengh = 0;
	uint16 pack_lengh = 0;
	uint16 lui16type = 0;
	memcpy(&lui16type,apIn,sizeof(uint16));
	
	if( lui16type == PACK_DCS_DNS_HEAD)
	{
		stru_DCS_DNS_HEAD dns_pack;
		dns_pack.UnPack(apIn,aiIn);
		memcpy(original_data,dns_pack.m_cDataBuf,dns_pack.m_iDatalen);
		original_lengh= dns_pack.m_iDatalen;
		//解压解密处理。。。。
		memcpy(pack_data,original_data,original_lengh);
		pack_lengh=original_lengh;
		memcpy(&lui16type,pack_data,sizeof(uint16));
		//
	}
	else
	{
		memcpy(pack_data,apIn,aiIn);
		pack_lengh = aiIn;
		//TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_HEAD 类型 错误。");
		//return 0;
	}
	switch(lui16type)
	{
	
	case PACK_DCS_DNS_LOGIN_RQ :
		{
			
			stru_DCS_DNS_LOGIN_RQ stru_dcs_dns_login_rq;
			stru_DCS_DNS_LOGIN_RS stru_dcs_dns_login_rs;
			if(0 != stru_dcs_dns_login_rq.UnPack(pack_data,pack_lengh))
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_LOGIN_RQ UnPack 错误。");
				return 0;
			}
			
			stru_dcs_dns_login_rs.m_iDnsIp = stru_dcs_dns_login_rq.m_iDnsIp;
			stru_dcs_dns_login_rs.m_iDnsId = stru_dcs_dns_login_rq.m_iDnsId;
			if( (aiOut = stru_dcs_dns_login_rs.Pack(apOut,DCS_DNS_BUFFER_LEN)) <=0)
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_LOGIN_RS Pack 错误。");
				return 0;
			}
			struct in_addr ip ;
			ip.s_addr = stru_dcs_dns_login_rs.m_iDnsIp;
			TRACE(1, "CDCSDealData::DCSDealData 类型 PACK_DCS_DNS_LOGIN_RS ip="<<inet_ntoa(ip)<<" id="<<stru_dcs_dns_login_rs.m_iDnsId);
			return 1;
		}
	case PACK_DCS_DNS_KEEP_LIVE_RQ :
		{
			stru_DCS_DNS_KEEP_LIVE_RQ pack_rq;
			stru_DCS_DNS_KEEP_LIVE_RS pack_rs;
			if(0 != pack_rq.UnPack(pack_data,pack_lengh))
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_KEEP_LIVE_RQ UnPack 错误。");
				return 0;
			}
			
			pack_rs.m_iDnsIp = pack_rq.m_iDnsIp;
			pack_rs.m_iDnsId = pack_rq.m_iDnsId;
			if(( aiOut = pack_rs.Pack(apOut,DCS_DNS_BUFFER_LEN) )<=0)
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_KEEP_LIVE_RS Pack 错误。");
				return 0;
			}
			struct in_addr ip ;
			ip.s_addr = pack_rs.m_iDnsIp;
			//TRACE(5, "CDCSDealData::DCSDealData 类型 PACK_DCS_DNS_KEEP_LIVE_RQ ip="<<inet_ntoa(ip)<<" id="<<pack_rs.m_iDnsId);
			return 1;
		}
	case PACK_DCS_DNS_LOGOUT_RQ :
		{
			stru_DCS_DNS_LOGOUT_RQ pack_rq;
			stru_DCS_DNS_LOGOUT_RQ pack_rs;
			if(0 != pack_rq.UnPack(pack_data,pack_lengh))
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_LOGOUT_RQ UnPack 错误。");
				return 0;
			}
			
			pack_rs.m_iDnsIp = pack_rq.m_iDnsIp;
			pack_rs.m_iDnsId = pack_rq.m_iDnsId;
			if(( aiOut = pack_rs.Pack(apOut,DCS_DNS_BUFFER_LEN) )<=0)
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_LOGOUT_RS Pack 错误。");
				return 0;
			}
			struct in_addr ip ;
			ip.s_addr = pack_rs.m_iDnsIp;
			//TRACE(1, "CDCSDealData::DCSDealData 类型 PACK_DCS_DNS_LOGOUT_RS ip="<<inet_ntoa(ip)<<" id="<<pack_rs.m_iDnsId);
			return 1;
		}
	case PACK_DCS_DNS_MESSAGE:
		{
			stru_DCS_DNS_MESSAGE pack_msg;
			if(0 != pack_msg.UnPack(pack_data,pack_lengh))
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_MESSAGEUnPack 错误。");
				return 0;
			}
			if(pack_msg.m_iDatalen <14 || pack_msg.m_iDatalen > DCS_DNS_BUFFER_LEN-14)
			{
				TRACE(1, "CDCSDealData::DCSDealData PACK_DCS_DNS_MESSAGEDatelen 错误。");
				return 0;
			}
			
			memcpy(apOut,pack_data,pack_lengh);
			aiOut = pack_lengh;
			struct in_addr ip ;
			ip.s_addr = pack_msg.m_iDnsIp;
			//TRACE(1, "CDCSDealData::DCSDealData 类型 PACK_DCS_DNS_MESSAGE ip="<<inet_ntoa(ip)<<" id="<<pack_msg.m_iDnsId);
			return 2;
		}
	default:
		{
			TRACE(1, "CDCSDealData::DCSDealData 未知包类型。类型："<<lui16type);
			break;
		}
	}
	return 0;
}
