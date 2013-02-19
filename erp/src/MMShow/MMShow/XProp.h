#pragma once

#define XProp(Type,Name) \
		private: \
			Type m_##Name; \
		public: \
			Type Get##Name(void) const { \
				return m_##Name; \
			} \
			void Set##Name(const Type &val) { \
				if (m_##Name != val) { \
					m_##Name = val; \
					SetModified(); \
				} \
			} \
			BOOL Equal##Name(const Type &val) { \
				return m_##Name == val;  \
			} \
			//__declspec(property( get=Get##Name,put=Set##Name)) Type Name;

#define XModifiedSetOnlyFlag() \
	public: \
		void SetModified(void) { \
			m_bModified = true; \
			} \
	private: \
		bool m_bModified; 

#define  XModifiedFlag() \
	public: \
		bool IsModified(void) const { \
			return m_bModified; \
		} \
		void SetModified(void) { \
			m_bModified = true; \
		} \
	private: \
		bool m_bModified; 



#define XStrProp(Name) XProp(CString,Name) 
#define XUintProp(Name) XProp(UINT,Name)
#define XIntProp(Name) XProp(INT,Name)
#define XBoolProp(Name) XProp(bool,Name)
#define XSizeProp(Name) XProp(CSize,Name)
#define XClrProp(Name) XProp(COLORREF,Name)
#define XTimeProp(Name) XProp(COleDateTime,Name)
