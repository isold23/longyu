using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

using System.Data;
using System.Data.SqlClient;

namespace AutoStoredProcedure
{
    public class StoredProcedure
    {
        private string m_strName;
        private bool m_bRet;
        private string m_strRecordsetType;
        private List<Parameter> m_params = new List<Parameter>();

        public string Name
        {
            get { return m_strName; }
        }

        public string RecordsetType
        {
            get { return m_strRecordsetType; }
        }

        public bool Ret
        {
            get { return m_bRet; }
        }

        public StoredProcedure(string strName, string strRecordsetType,bool bRet)
        {
            m_strRecordsetType = strRecordsetType;
            m_strName = strName;
            m_bRet = bRet;
        }

        public void AddParam(string strSqlName, string strSqlType, string strSqlDirection, int nLength)
        {
            Parameter param = new Parameter(strSqlName, strSqlType, strSqlDirection, nLength);
            m_params.Add(param);
        }

        public Parameter ParamAt(int i)
        {
            return m_params[i];
        }

        public int IndexOfParam(Parameter param)
        {
            return m_params.IndexOf(param);
        }

        public int ParamCount
        {
            get { return m_params.Count; }
        }
    };
}
