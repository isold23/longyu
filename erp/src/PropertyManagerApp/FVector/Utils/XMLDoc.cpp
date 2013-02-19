#include "stdafx.h"
#include "XmlDoc.h"
#ifndef _AFX
#include <cassert>
#define ASSERT assert
#endif
#define MAX_NODE_NAME_LEN 256

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// CXmlNode//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************
								Name
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get name of the node
//////////////////////////////////////////////////////////////////////////
CString CXmlNode::GetName(void)
{
	try
	{
		return (m_node!=NULL ? (LPCTSTR)m_node->nodeName:CString());
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return CString();
	}
}

/************************************************************************
								File
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get file of the node
//////////////////////////////////////////////////////////////////////////
CXmlDoc CXmlNode::GetDoc(void)
{
	CXmlDoc file;
	try
	{
		if (m_node != NULL)
			file.m_doc = m_node->GetownerDocument();
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return file;
}

/************************************************************************
	                               Value
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get the value of the node
//////////////////////////////////////////////////////////////////////////
CString CXmlNode::GetValue(void)
{
	try
	{ 
		return (m_node!=NULL ? (LPCTSTR)m_node->text : CString());
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return CString();
	}
}

//////////////////////////////////////////////////////////////////////////
// Set the value of the node
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::SetValue(const CString& strText)
{
	try
	{
		if (m_node == NULL)
		{
			return FALSE;
		}
		else
		{
			m_node->text = (LPCTSTR)strText;
			return TRUE;
		}
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}
/************************************************************************
								Parent
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get parent node of the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetParent(void)
{
	CXmlNode node;
	
	try
	{
		if (m_node != NULL)
			node.m_node = m_node->parentNode;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}
/************************************************************************
							text
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get the text of the node
//////////////////////////////////////////////////////////////////////////
CString CXmlNode::GetText(void)
{
	try
	{
		return (m_node!=NULL ? (LPCTSTR)m_node->xml : CString());
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return CString();
	}
}

/************************************************************************
								Attribute
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get count of attributes of the node
//////////////////////////////////////////////////////////////////////////
int CXmlNode::GetAttribCount(void)
{
	try
	{
		return  (m_node!=NULL ? m_node->attributes->length : 0);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
// If the specified attrib exists
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::HasAttrib(IN LPCTSTR pcszAttrib)
{
	try
	{
		return (m_node==NULL ? FALSE : (m_node->attributes->getNamedItem(pcszAttrib)!=NULL));
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
// Get specified index of attributes of the node
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, CString& strVal)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		strVal = (LPCTSTR)(_bstr_t)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, SHORT &sVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		sVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, LONG &lVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		lVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, FLOAT &fVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		fVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, DOUBLE &dbVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		dbVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, bool &bVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		bVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, BYTE &btVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		btVal = node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, CHAR &cVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		cVal = (BYTE)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, WORD &wVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		wVal = (SHORT)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, ULONG &ulVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		ulVal = (ULONG)(long)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, INT &nVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		nVal = (INT)(long)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


BOOL CXmlNode::GetAttrib(int nIndex,CString& strAttrib, UINT &nVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		nVal = (UINT)(long)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::GetBigUIntAttrib(IN int nIndex,OUT CString& strAttrib, OUT LONGLONG &nVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		nVal = (LONGLONG)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::GetBitIntAttrib(IN int nIndex,OUT CString& strAttrib, OUT  ULONGLONG &nVal)
{
	try
	{		
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->item[nIndex];
		strAttrib = (LPCTSTR)node->nodeName;
		nVal = (ULONGLONG)node->nodeValue;
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}




//////////////////////////////////////////////////////////////////////////
// Get value of specified attributes
//////////////////////////////////////////////////////////////////////////
CString CXmlNode::GetStringAttrib(LPCTSTR pcszAttrib)
{ 
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? CString() : (LPCTSTR)(_bstr_t)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return CString();
	}
}
SHORT CXmlNode::GetShortAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (SHORT)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0; 
	}
}

LONG CXmlNode::GetLongAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (LONG)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}

FLOAT CXmlNode::GetFloatAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0.0f : node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0.0f;
	}
}


DOUBLE CXmlNode::GetDoubleAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0.0 : node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0.0;
	}
}


bool CXmlNode::GetBoolAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? false : node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return false;
	}
}


BYTE CXmlNode::GetByteAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (BYTE)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


CHAR CXmlNode::GetCharAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (BYTE)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


WORD CXmlNode::GetWordAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (SHORT)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


ULONG CXmlNode::GetULongAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (LONG)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


INT CXmlNode::GetIntAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (INT)(long)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


UINT CXmlNode::GetUIntAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (LONG)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


LONGLONG CXmlNode::GetBigUIntAttrib(IN LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (ULONGLONG)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}

ULONGLONG CXmlNode::GetBitIntAttrib(IN LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? 0 : (ULONGLONG)node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}


_variant_t CXmlNode::GetVariantAttrib(IN LPCTSTR pcszAttrib)
{
	try
	{
		MSXML2::IXMLDOMNodePtr node = m_node->attributes->getNamedItem(pcszAttrib);
		return  (node == NULL ? _variant_t() : node->nodeValue);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return _variant_t();
	}
}

//////////////////////////////////////////////////////////////////////////
// Set the value of specified attribute of the node 
// or insert a new attribute if the specified attribute doesn't exist
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,LPCTSTR pcszVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (_bstr_t)pcszVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,SHORT sVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = sVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,LONG lVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = lVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(IN LPCTSTR pcszAttrib,IN LONGLONG nVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = nVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(IN LPCTSTR pcszAttrib,IN ULONGLONG nVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = nVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,FLOAT fVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = fVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,DOUBLE dbVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = dbVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}
 

//BOOL CXmlNode::SetAttrib(IN LPCTSTR pcszAttrib,IN _variant_t variant)
//{
//	MSXML2::IXMLDOMAttributePtr attribPtr;
//	MSXML2::IXMLDOMDocumentPtr docPtr;
//
//	try
//	{	
//		docPtr = m_node->ownerDocument;
//		attribPtr = docPtr->createAttribute(_bstr_t(strAttrib));
//		attribPtr->nodeValue = variant;
//		m_node->attributes->setNamedItem(attribPtr);
//		return TRUE;
//	}
//	catch (.../*_com_error &ex*/)
//	{
//		//TRACE(ex.Description().GetBSTR());
//		return FALSE;
//	}
//}



//BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,bool bVal)
//{
//	MSXML2::IXMLDOMAttributePtr attribPtr;
//	MSXML2::IXMLDOMDocumentPtr docPtr;
//
//	try
//	{	
//		docPtr = m_node->ownerDocument;
//		attribPtr = docPtr->createAttribute(_bstr_t(strAttrib));
//		attribPtr->nodeValue = bVal;
//		m_node->attributes->setNamedItem(attribPtr);
//		return TRUE;
//	}
//	catch (.../*_com_error &ex*/)
//	{
//		//TRACE(ex.Description().GetBSTR());
//		return FALSE;
//	}
//}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,BYTE btVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = btVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,CHAR cVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (long)cVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,WORD wVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (long)wVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,ULONG ulVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (long)ulVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,INT nVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (long)nVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

BOOL CXmlNode::SetAttrib(LPCTSTR pcszAttrib,UINT nVal)
{
	MSXML2::IXMLDOMAttributePtr attribPtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{	
		docPtr = m_node->ownerDocument;
		attribPtr = docPtr->createAttribute(_bstr_t(pcszAttrib));
		attribPtr->nodeValue = (long)nVal;
		m_node->attributes->setNamedItem(attribPtr);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
// Remove a specified attribute of the node
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::RemoveAttrib(LPCTSTR pcszAttrib)
{
	try
	{
		m_node->attributes->removeNamedItem(_bstr_t(pcszAttrib));
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
// Remove all attributes of the node
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::RemoveAllAttrib(void)
{
	MSXML2::IXMLDOMNodePtr nodePtr;
	try
	{
		while ( m_node->attributes->length != 0)
		{
			nodePtr = m_node->attributes->item[0];
			m_node->attributes->removeNamedItem(nodePtr->nodeName);
		}
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}


/************************************************************************
								Child
*************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Get count of all child nodes of the node
//////////////////////////////////////////////////////////////////////////
int CXmlNode::GetChildCount(void)
{
	try
	{
		return m_node->childNodes->length;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return 0;
	}
}
//////////////////////////////////////////////////////////////////////////
// Get count of all child nodes with the specific name of the node
//////////////////////////////////////////////////////////////////////////
int CXmlNode::GetChildCount(LPCTSTR pcszNodeName)
{
	int cnt;
	MSXML2::IXMLDOMNodePtr nodePtr;
	
	try
	{
		cnt = 0;
		nodePtr = m_node->firstChild;
		while (nodePtr != NULL)
		{  
			if ((CString)(LPCTSTR)nodePtr->nodeName == pcszNodeName)
			{
				// node.m_node = nodePtr;
				cnt++;
			}
			nodePtr = nodePtr->nextSibling;
		}
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return cnt;
}
//////////////////////////////////////////////////////////////////////////
// Get the specified index child node of the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetChild(int nIndex)
{
	CXmlNode node;

	try
	{
		node.m_node = m_node->childNodes->item[nIndex];
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}

//////////////////////////////////////////////////////////////////////////
// Get the first child node of the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetFirstChild(void)
{
	CXmlNode node;

	try
	{
		node.m_node = m_node->firstChild;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}

//////////////////////////////////////////////////////////////////////////
// Get the next child node of the node to the specified child node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetNextChild(CXmlNode &nodeChild)
{
	CXmlNode node;

	try
	{
		node.m_node = nodeChild.m_node->nextSibling;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}

//////////////////////////////////////////////////////////////////////////
// Get the first child node of the specified name from the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetFirstChild(LPCTSTR pcszName)
{
	CXmlNode node;
	MSXML2::IXMLDOMNodePtr nodePtr;
	
	try
	{
		nodePtr = m_node->firstChild;
		while (nodePtr != NULL)
		{  
			if ((CString)(LPCTSTR)nodePtr->nodeName == pcszName)
			{
				node.m_node = nodePtr;
				break;
			}
			nodePtr = nodePtr->nextSibling;
		}
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}

//////////////////////////////////////////////////////////////////////////
// Get the next child node with the specified name to the specified node 
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetNextChild(CXmlNode &nodeChild,LPCTSTR pcszName)
{
	CXmlNode node;
	MSXML2::IXMLDOMNodePtr nodePtr;
	
	try
	{
		nodePtr = nodeChild.m_node->nextSibling;
		while (nodePtr != NULL)
		{  
			if ((CString)(LPCTSTR)nodePtr->nodeName == pcszName)
			{
				node.m_node = nodePtr;
				break;
			}
			nodePtr = nodePtr->nextSibling;
		}
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}

//////////////////////////////////////////////////////////////////////////
// Get the child node of the the name with the specified path
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetChild(LPCTSTR pcszChildPath)
{
	//////////////////////////////////////////////////////////////////////////
	// if strChildPath is "\a\b\c\d"
	// first, get child node a
	// second, get child node b of a
	// just do it recursively until d which with no '\' at after 'd'
	//////////////////////////////////////////////////////////////////////////

	CXmlNode node;

	// If the path is null then return this node own
	//if (strChildPath == CString())
	//{
	//	return *this;
	//}

	ASSERT(pcszChildPath[0]!='\0' && pcszChildPath[0] == '\\');

	LPTSTR pszPath = (LPTSTR)pcszChildPath + 1;
	LPTSTR pos = _tcschr(pszPath,'\\');
	
	// If this path doesn't have '\\'
	// then this function is used to get the child node with the specified name --- strChildPath
	if (pos == NULL)
	{
		return GetFirstChild(pszPath);
	}
	else
	{
		// Get the name of the next layer child node
		UINT_PTR nChildNameLen = pos - pszPath;
		TCHAR szChildName[MAX_NODE_NAME_LEN]; // (strChildPath.begin()+1,strChildPath.begin()+pos);
		memcpy(szChildName,pszPath,nChildNameLen);
		szChildName[nChildNameLen] = _T('\0');


		// Get the first child node with the node name --- strChild 
		node = GetFirstChild(szChildName);
		
		// Get the next layer child node recursively
		return (node.IsNull() ?  node : node.GetChild(pos));
	}
}

//////////////////////////////////////////////////////////////////////////
// Get the child node of withe specified path '[][][]' beginning at a specific pos
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::GetChild(const std::vector<CString> &vecChild, int nPos)
{
	CXmlNode node;
	if (nPos >= (int)vecChild.size())
		return node;

	node = GetFirstChild(vecChild[nPos]);
	if (node.IsNull() || ++nPos == vecChild.size())
		return node;
	
	return node.GetChild(vecChild,nPos);

}


//////////////////////////////////////////////////////////////////////////
// Add a new child node with the specified name the the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::InsertChildBefore(LPCTSTR pcszName,CXmlNode& node)
{
	CXmlNode nodeNew;
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;
	
	try
	{
		docPtr = m_node->ownerDocument;
		nodePtr = docPtr->createNode((long)NODE_ELEMENT,pcszName,_T(""));
		nodeNew.m_node = m_node->insertBefore(nodePtr,&_variant_t(node.m_node));
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return nodeNew;
}

//////////////////////////////////////////////////////////////////////////
// Append a new child node to all the  the node with specified name
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::AppendChild(LPCTSTR pcszName)
{
	CXmlNode nodeNew;
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMDocumentPtr docPtr;

	try
	{
		docPtr = m_node->ownerDocument;
		nodePtr = docPtr->createNode((long)NODE_ELEMENT,pcszName,_T(""));
		nodeNew.m_node = m_node->appendChild(nodePtr);
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return nodeNew;
}

//////////////////////////////////////////////////////////////////////////
// Append an existed child node to the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::AppendChild(CXmlNode &node)
{
	CXmlNode n;
	n.m_node = m_node->appendChild(node.m_node);
	return node;
}


//////////////////////////////////////////////////////////////////////////
// Remove the child node with the specified index
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::RemoveChild(int nIndex)
{
	CXmlNode node;
	MSXML2::IXMLDOMNodePtr nodePtr;

	try
	{
		nodePtr = m_node->childNodes->item[nIndex];
		node.m_node = m_node->removeChild(nodePtr);
		return node;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return node;
	}
}

//////////////////////////////////////////////////////////////////////////
// Remove all the child nodes with the specified name
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::RemoveChild(LPCTSTR pcszName)
{
	CXmlNode node;
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMNodePtr tempPtr;


	try
	{
		nodePtr = m_node->firstChild;
		while (nodePtr != NULL)
		{ 
			if ((CString)(LPCTSTR)nodePtr->nodeName == pcszName)
			{
				tempPtr = nodePtr->nextSibling;
				node.m_node = m_node->removeChild(nodePtr);
				nodePtr = tempPtr;
				break;
			}
			else
			{
				nodePtr = nodePtr->nextSibling;
			}
		}
		return node;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return node;
	}
}

//////////////////////////////////////////////////////////////////////////
// Remove the specified node of the node
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlNode::RemoveChild(CXmlNode &node)
{
	CXmlNode n;
	try
	{
		m_node->removeChild(node.m_node);
		return node;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return n;
	}
}

//////////////////////////////////////////////////////////////////////////
// Remove all child nodes of the node
//////////////////////////////////////////////////////////////////////////
BOOL CXmlNode::RemoveAllChild(void)
{
	MSXML2::IXMLDOMNodePtr nodePtr;
	MSXML2::IXMLDOMNodePtr tempPtr;

	try
	{
		nodePtr = m_node->firstChild;
		while (nodePtr != NULL)
		{ 
			tempPtr = nodePtr->nextSibling;
			m_node->removeChild(nodePtr);
			nodePtr = tempPtr;
		}
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// CXmlDoc//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlDoc::CXmlDoc(void)
{
	m_doc.CreateInstance(__uuidof(MSXML2::DOMDocument));
}

CXmlDoc::~CXmlDoc(void)
{
	m_doc.Release();
}

//////////////////////////////////////////////////////////////////////////
// Load the file from a specified path
//////////////////////////////////////////////////////////////////////////
BOOL CXmlDoc::Load(LPCTSTR pcszPathName)
{	
	BOOL bRet = m_doc->load(pcszPathName);

	if (bRet)
		m_nodeRoot.m_node = m_doc->documentElement;
	
	return bRet;		
}

//////////////////////////////////////////////////////////////////////////
// Save the file to a specified path
//////////////////////////////////////////////////////////////////////////
BOOL CXmlDoc::Save(LPCTSTR pcszPathName)
{
	try
	{
		m_doc->save(pcszPathName);
		return TRUE;
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
// Load the file from text
//////////////////////////////////////////////////////////////////////////
BOOL CXmlDoc::SetText(LPCTSTR pcszText)
{
	BOOL bRet = m_doc->loadXML(pcszText);
	
	if (bRet)
		m_nodeRoot.m_node = m_doc->documentElement;
	
	return 	bRet;
}

//////////////////////////////////////////////////////////////////////////
// Get the text of the file
//////////////////////////////////////////////////////////////////////////
CString CXmlDoc::GetText(void)
{
	return (LPCTSTR)m_doc->xml;
}

//////////////////////////////////////////////////////////////////////////
// Create a root node with the specified name
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlDoc::CreateRoot(LPCTSTR pcszName,LPCTSTR pcszEncoding)
{
	CString strTemp;
	if (pcszEncoding != NULL)
	{
		strTemp = _T("<?xml version=\"1.0\" encoding=\"");
		strTemp += pcszEncoding;
		strTemp += _T("\"?>");
	}
	strTemp += _T('<');
	strTemp += pcszName;
	strTemp += _T("/>");

	if (m_doc->loadXML((LPCTSTR)strTemp))
	{
		m_nodeRoot.m_node = m_doc->documentElement;
	}
	else
	{
		m_nodeRoot.m_node = NULL;
	}

	return m_nodeRoot;
}

//////////////////////////////////////////////////////////////////////////
// Create a node withe specified name
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlDoc::CreateNode(IN LPCTSTR pcszName)
{
	CXmlNode node;

	try
	{ 
		node.m_node = m_doc->createNode((long)NODE_ELEMENT,pcszName,_T(""));
	}
	catch (.../*_com_error &ex*/)
	{
		//TRACE(ex.Description().GetBSTR());
	}

	return node;
}



//////////////////////////////////////////////////////////////////////////
// Get the root node of the file
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlDoc::GetRoot(void)
{
	return m_nodeRoot;
}

//////////////////////////////////////////////////////////////////////////
// Get the child node with the specified path of the file
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlDoc::GetChild(LPCTSTR pcszChildPath)
{
	CXmlNode node;
	if (pcszChildPath[0] != '\\' || m_nodeRoot.IsNull())
		return node;
  
	LPTSTR pszPath = (LPTSTR)pcszChildPath + 1;
	LPTSTR pos = _tcschr(pszPath,'\\');
	if (pos != NULL)
	{
		return m_nodeRoot.GetChild(pos);
	}
	else
	{
		if (m_nodeRoot.Name != pszPath)
			return node;
		else
			return m_nodeRoot;
	} 
}


//////////////////////////////////////////////////////////////////////////
// Get the child node of withe specified path '[][][]' beginning at a specific pos
//////////////////////////////////////////////////////////////////////////
CXmlNode CXmlDoc::GetChild(const std::vector<CString> &vecChild, int nPos)
{
	CXmlNode node;

	if (m_nodeRoot.IsNull() || 
			nPos>=(int)vecChild.size()||
				m_nodeRoot.Name != vecChild[0])
		return node;

	return m_nodeRoot.GetChild(vecChild,++nPos);
}