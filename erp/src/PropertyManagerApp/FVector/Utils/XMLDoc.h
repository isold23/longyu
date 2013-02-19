#pragma once

#import "msxml3.dll" 
 
#include <vector>
#if _MSC_VER > 1200
#include <atlstr.h>
#endif 

#ifndef NODE_ELEMENT
#define NODE_ELEMENT 1
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// CXmlNode//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlNode
{
	friend class CXmlDoc;
public:
	/************************************************************************
									IsNull
	*************************************************************************/
	bool IsNull(void) const;

	/************************************************************************
									File
	*************************************************************************/
	_declspec(property(get=GetDoc))CXmlDoc File;
	CXmlDoc GetDoc(void);

	/************************************************************************
									Name
	*************************************************************************/
	// Get name of the node
	_declspec(property(get=GetName))CString Name;
	CString GetName(void);

	/************************************************************************
	                               Value
	*************************************************************************/
	_declspec(property(get=GetValue,put=SetValue))CString Value;
	CString GetValue(void);	// Load the node from text
	BOOL SetValue(IN const CString& strText);

	/************************************************************************
									Parent
	*************************************************************************/
	// Get parent node of the node
	_declspec(property(get=GetParent))CXmlNode Parent;
	CXmlNode GetParent(void);

	/************************************************************************
									Load
	*************************************************************************/
	// Get the text of the node
	_declspec(property(get=GetText))CString Text;
	CString GetText(void);

	/************************************************************************
	                               Attribute
	*************************************************************************/
	// Get count of attributes of the node
	int GetAttribCount(void);
	// If the specified attrib exists
	BOOL HasAttrib(IN LPCTSTR pcszAttrib);
	// Get specified index of attributes of the node
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT CString& strVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT SHORT &sVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT LONG &lVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT FLOAT &fVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT DOUBLE &dbVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT bool &bVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT BYTE &btVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT CHAR &cVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT WORD &wVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT ULONG &ulVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT INT &nVal);
	BOOL GetAttrib(IN int nIndex,OUT CString &strAttrib, OUT UINT &nVal);

	BOOL GetBigUIntAttrib(IN int nIndex,OUT CString& strAttrib, OUT LONGLONG &nVal);
	BOOL GetBitIntAttrib(IN int nIndex,OUT CString& strAttrib, OUT ULONGLONG &nVal); 

	// Get value of specified attributes
	CString GetStringAttrib(IN LPCTSTR pcszAttrib);
	SHORT GetShortAttrib(IN LPCTSTR pcszAttrib);
	LONG GetLongAttrib(IN LPCTSTR pcszAttrib);
	FLOAT GetFloatAttrib(IN LPCTSTR pcszAttrib);
	DOUBLE GetDoubleAttrib(IN LPCTSTR pcszAttrib);
	bool GetBoolAttrib(IN LPCTSTR pcszAttrib);
	BYTE GetByteAttrib(IN LPCTSTR pcszAttrib);
	CHAR GetCharAttrib(IN LPCTSTR pcszAttrib);
	WORD GetWordAttrib(IN LPCTSTR pcszAttrib);
	ULONG GetULongAttrib(IN LPCTSTR pcszAttrib);
	INT GetIntAttrib(IN LPCTSTR pcszAttrib);
	UINT GetUIntAttrib(IN LPCTSTR pcszAttrib);


	LONGLONG GetBigUIntAttrib(IN LPCTSTR pcszAttrib);
	ULONGLONG GetBitIntAttrib(IN LPCTSTR pcszAttrib);                     

	_variant_t GetVariantAttrib(IN LPCTSTR pcszAttrib);


	// Set the value of specified attribute of the node 
	// or insert a new attribute if the specified attribute doesn't exist
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN LPCTSTR pcszVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN SHORT sVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN LONG lVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN FLOAT fVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN DOUBLE dbVal);
	//BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN bool bVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN BYTE btVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN CHAR cVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN WORD wVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN ULONG ulVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN INT nVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN UINT nVal);

	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN LONGLONG nVal);
	BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN ULONGLONG nVal);                   

	// BOOL SetAttrib(IN LPCTSTR pcszAttrib,IN _variant_t variant);

	// Remove a specified attribute of the node
	BOOL RemoveAttrib(IN LPCTSTR pcszAttrib);
	// Remove all attributes of the node
	BOOL RemoveAllAttrib(void);

	/************************************************************************
									Child
	*************************************************************************/
	// Get count of all child nodes of the node
	int GetChildCount(void);
	_declspec(property(get=GetChildCount))int ChildCount;
	// Get count of all child nodes with the specific name of the node
	int GetChildCount(IN LPCTSTR pcszNodeName);
	// Get the specified index child node of the node
	CXmlNode GetChild(IN int nIndex);
	_declspec(property(get=GetChild))CXmlNode Child[];

	// Get the first child node of the node
	CXmlNode GetFirstChild(void);
	// Get the next child node of the node to the specified child node 
	CXmlNode GetNextChild(IN CXmlNode &nodeChild);

	// Get the first child node of the specified name from the node
	CXmlNode GetFirstChild(IN LPCTSTR pcszName);
	// Get the next child node with the specified name to the specified node 
	CXmlNode GetNextChild(IN CXmlNode &nodeChild,IN LPCTSTR pcszName);
	
	// Get the child node with the specified path format '\\\\\'
	CXmlNode GetChild(IN LPCTSTR pcszChildPath);
	// Get the child node of withe specified path '[][][]' beginning at a specific pos
	CXmlNode GetChild(IN const std::vector<CString>& vecChild, int nPos = 0);
	
	// Insert a new child node with the specified name before a specified node
	// if the specifed node is null, the new node is appended to all the child nodes
	CXmlNode InsertChildBefore(IN LPCTSTR pcszName,IN CXmlNode& node);
	// Append a new child node to all the  the node with specified name
	CXmlNode AppendChild(IN LPCTSTR pcszName);
	// Append an existed child node to the node
	CXmlNode AppendChild(IN CXmlNode &node);

	// Remove the child node with the specified index
	CXmlNode RemoveChild(IN int nIndex);
	// Remove all the child nodes with the specified name
	CXmlNode RemoveChild(IN LPCTSTR pcszName);
	// Remove the specified node of the node
	CXmlNode RemoveChild(IN CXmlNode &node);
	// Remove all child nodes of the node
	BOOL RemoveAllChild(void);

private:
	
	MSXML2::IXMLDOMNodePtr m_node;
};





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// CXmlDoc//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlDoc
{
	friend class CXmlNode;
public:
	CXmlDoc(void);
	~CXmlDoc(void);

	/************************************************************************
						IsNull
	*************************************************************************/
	bool IsNull(void) const;

	// Load the file from a specified path
	BOOL Load(IN LPCTSTR pcszPathName);
	// Save the file to a specified path
	BOOL Save(IN LPCTSTR pcszPathName);

	_declspec(property(get=GetText,put=SetText))CString Text;
	// Load the file from text
	BOOL SetText(IN LPCTSTR pcszText);
	// Get the text of the file
	CString GetText(void);

	// Create a root node with the specified name
	CXmlNode CreateRoot(IN LPCTSTR pcszName,LPCTSTR pcszEncoding=NULL);

	// Create a node withe specified name
	CXmlNode CreateNode(IN LPCTSTR pcszName);

	_declspec(property(get=GetRoot))CXmlNode Root;
	// Get the root node of the file
	CXmlNode GetRoot(void);
	// Get the child node with the specified path of the file with the format '\\\\'
	CXmlNode GetChild(IN LPCTSTR pcszChildPath);
	// Get the child node of withe specified path '[][][]' beginning at a specific pos
	CXmlNode GetChild(IN const std::vector<CString> &vecChild, int nPos = 0);

private:
	MSXML2::IXMLDOMDocumentPtr m_doc;
	CXmlNode m_nodeRoot;
};

inline bool CXmlNode::IsNull(void) const {
	return m_node == NULL;
}

inline bool CXmlDoc::IsNull(void) const {
	return m_doc == NULL;
}
