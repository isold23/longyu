#include "dns_crs.h"

int stru_DNS_CRS_LOGIN_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_i32GroupId);
	return 1;
}

int stru_DNS_CRS_LOGIN_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DNS_CRS_KEEP_LIVE_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_i32GroupId);
	return 1;
}

int stru_DNS_CRS_KEEP_LIVE_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DNS_CRS_LOGOUT_RQ::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_i32GroupId);
	return 1;
}

int stru_DNS_CRS_LOGOUT_RS::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_iDnsId);
	return 1;
}

int stru_DNS_CRS_MESSAGE::Serialize(CStandardSerialize &aoStandardSerialize)
{
	aoStandardSerialize.Serialize(m_i32NodeId);
	aoStandardSerialize.Serialize(m_i32GroupId);
	aoStandardSerialize.Serialize(m_i32TargetNode);
	aoStandardSerialize.Serialize(m_i32TargetGroup);
	aoStandardSerialize.Serialize(m_iDnsId);
	aoStandardSerialize.Serialize(m_iDataLen);
	aoStandardSerialize.Serialize(m_DataBuffer,m_iDataLen,DNS_CRS_BUFFER_LEN +1);
	return 1;
}
























