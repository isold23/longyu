using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace AutoStoredProcedure
{
    class MSSql2000Provider : DBProvider
    {
        static public MSSql2000Provider Inst = new MSSql2000Provider();

        MSSql2000Provider()
        {
            m_strGetSPSql = "SELECT name FROM sysobjects WHERE xtype='P' AND status>=0 AND name NOT LIKE 'sp[_]%'";


            m_strGetParamSql = "SELECT sysobjects.name AS SPName, syscolumns.name AS ParamName,syscolumns.colorder AS Pos,";
            m_strGetParamSql += "systypes.name AS Type,syscolumns.isoutparam AS Direction,syscolumns.length AS Len ";
            m_strGetParamSql += "FROM syscolumns LEFT JOIN sysobjects ON sysobjects.id=syscolumns.id,systypes ";
            m_strGetParamSql += "WHERE sysobjects.xtype='P'AND sysobjects.status>=0 AND syscolumns.xtype=systypes.xtype AND systypes.name<>'sysname' AND sysobjects.name NOT LIKE 'sp[_]%' ";
            m_strGetParamSql += "ORDER BY SPName,Pos";
        }
        
        protected override void GetRow(DataRow row, SqlDataReader reader)
        {
            row["SPName"] = reader["SPName"];
            row["Pos"] = reader["Pos"];
            row["Direction"] = (int)reader["Direction"]==0 ? "in":"out";
            row["ParamName"] = reader["ParamName"];
            row["Type"] = reader["Type"];
            row["Len"] = reader["Len"];
        }
    }
}
