using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace AutoStoredProcedure
{
    public abstract class DBProvider
    {
        protected string m_strGetSPSql;
        protected string m_strGetParamSql;

        public string SPSql
        {
            get { return m_strGetSPSql; }
        }

        public string ParamSql
        {
            get { return m_strGetParamSql; }
        }

        public DataTable GetDataTable(SqlDataReader reader)
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("SPName");
            dt.Columns.Add("Pos");
            dt.Columns.Add("Direction");
            dt.Columns.Add("ParamName");
            dt.Columns.Add("Type");
            dt.Columns.Add("Len");


            while (reader.Read())
            {
                DataRow row = dt.NewRow();
                GetRow(row, reader);
                dt.Rows.Add(row);
            }
            return dt;
        }

        protected abstract void GetRow(DataRow row, SqlDataReader reader);
    }
}
