using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace AutoStoredProcedure
{
    public abstract class SPCreator
    {
        public abstract string GenClassBegin(bool bOutterConn, bool bShortConn);
        public abstract string Gen(StoredProcedure sp, bool bOutterConn, bool bShortConn);
        public abstract string GenClassEnd(bool bOutterConn, bool bShortConn);

        public Hashtable RecordsetTypeMap
        {
            get { return m_mapRecordsetType; }
        }

        public Hashtable ParamTypeMap
        {
            get { return m_mapParamType; }
        }

        public Hashtable ParamDBTypeMap
        {
            get { return m_mapParamDBType; }
        }

        private Hashtable m_mapRecordsetType = new Hashtable();
        private Hashtable m_mapParamType = new Hashtable();
        private Hashtable m_mapParamDBType = new Hashtable();
    };
}
