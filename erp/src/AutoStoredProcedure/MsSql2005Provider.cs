using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace AutoStoredProcedure
{
    class MSSql2005Provider : DBProvider
    {
        static public MSSql2005Provider Inst = new MSSql2005Provider();

        private MSSql2005Provider()
        {
            m_strGetSPSql = "SELECT name FROM sys.all_objects WHERE (type = 'P') AND (is_ms_shipped = 0)";
            m_strGetParamSql = "SELECT specific_name AS SPName,ordinal_position AS Pos,parameter_mode AS Direction,parameter_name AS ParamName,data_type AS Type,character_octet_length AS Len FROM information_schema.parameters ORDER BY specific_name,ordinal_position";
        }

        protected override void GetRow(DataRow row, SqlDataReader reader)
        {
            row["SPName"] = reader["SPName"];
            row["Pos"] = reader["Pos"];
            row["Direction"] = reader["Direction"];
            row["ParamName"] = reader["ParamName"];
            row["Type"] = reader["Type"];
            row["Len"] = reader["Len"];        
        }
    }
}
