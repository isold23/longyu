#include "dcs_dns.h"

int stru_DCS_DNS_LOGIN_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_LOGIN_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_KEEP_LIVE_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_KEEP_LIVE_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_LOGOUT_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_LOGOUT_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DCS_DNS_HEAD::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDatalen);
	aoStandardSerialize.Serialize(m_cDataBuf,m_iDatalen);
	return 1;
}

int stru_DCS_DNS_MESSAGE::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_iDnsIp);
	aoStandardSerialize.Serialize(m_iDnsId);
	aoStandardSerialize.Serialize(m_iDatalen);
	aoStandardSerialize.Serialize(m_cDataBuf,m_iDatalen,DCS_DNS_BUFFER_LEN +1);
	return 1;
}

