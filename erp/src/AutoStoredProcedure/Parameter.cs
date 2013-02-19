using System;
using System.Collections.Generic;
using System.Text;

namespace AutoStoredProcedure
{
    public class Parameter
    {
        private string m_strName;
        private string m_strSqlName;
        private string m_strSqlType;
        private string m_strSqlDirection;
        private int m_nLength;

        public string Name
        {
            get { return m_strName; }
        }

        public string SqlName
        {
            get { return m_strSqlName; }
        }

        public string SqlType
        {
            get { return m_strSqlType; }
        }

        public string SqlDirection
        {
            get { return m_strSqlDirection; }
        }

        public int SqlLen
        {
            get { return m_nLength; }
        }

        public Parameter(string strSqlName, string strSqlType, string strSqlDirection, int nLength)
        {
            m_strSqlName = strSqlName;
            m_strName = m_strSqlName.Replace("@", "");

            m_strSqlType = strSqlType;
            m_strSqlDirection = strSqlDirection.ToLower();
            m_nLength = nLength;
        }
    };


}
