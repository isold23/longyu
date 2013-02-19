using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;

namespace AutoStoredProcedure
{
    public class CSharpSPCreator : SPCreator
    {
        public static CSharpSPCreator Inst = new CSharpSPCreator();

        private CSharpSPCreator()
        {
            RecordsetTypeMap["INT64"] = "Int64";
            RecordsetTypeMap["INT"] = "int";
            RecordsetTypeMap["SHORT"] = "short";
            RecordsetTypeMap["BYTE"] = "byte";
            RecordsetTypeMap["BOOL"] = "bool";
            RecordsetTypeMap["DOUBLE"] = "double";
            RecordsetTypeMap["FLOAT"] = "float";
            RecordsetTypeMap["DATETIME"] = "DateTime";
            RecordsetTypeMap["STRING"] = "string";
            RecordsetTypeMap["RECORDSET"] = "SqlDataReader";

            ParamTypeMap["nvarchar"] = "string";
            ParamTypeMap["varchar"] = "string";
            ParamTypeMap["nchar"] = "string";
            ParamTypeMap["char"] = "string";
            ParamTypeMap["bit"] = "bool";
            ParamTypeMap["tinyint"] = "byte";
            ParamTypeMap["smallint"] = "short";
            ParamTypeMap["int"] = "int";
            ParamTypeMap["bigint"] = "Int64";
            ParamTypeMap["float"] = "double";
            ParamTypeMap["decimal"] = "float";
            ParamTypeMap["real"] = "float";
            ParamTypeMap["datetime"] = "DateTime";

            ParamDBTypeMap["nvarchar"] = "SqlDbType.NVarChar";
            ParamDBTypeMap["varchar"] = "SqlDbType.VarChar";
            ParamDBTypeMap["char"] = "SqlDbType.Char";
            ParamDBTypeMap["bit"] = "SqlDbType.Bit";
            ParamDBTypeMap["tinyint"] = "SqlDbType.TinyInt";
            ParamDBTypeMap["smallint"] = "SqlDbType.SmallInt";
            ParamDBTypeMap["int"] = "SqlDbType.Int";
            ParamDBTypeMap["bigint"] = "SqlDbType.BigInt";
            ParamDBTypeMap["float"] = "SqlDbType.Float";
            ParamDBTypeMap["decimal"] = "SqlDbType.Decimal";
            ParamDBTypeMap["real"] = "SqlDbType.Real";
            ParamDBTypeMap["datetime"] = "SqlDbType.DateTime";
        }

        public override string GenClassBegin(bool bOutterConn,bool bShortConn)
        {
            return string.Empty;
        }

        public override string GenClassEnd(bool bOutterConn, bool bShortConn)
        {
            return string.Empty;
        }

        public override string Gen(StoredProcedure sp, bool bOutterConn, bool bShortConn)
        {
            StringBuilder sb = new StringBuilder();

            Parameter param;
            int i, cnt = sp.ParamCount;

            // Comment
            // Name
            sb.Append("// STORED PROCEDURE NAME:");
            sb.Append(sp.Name);
            sb.Append("\r\n// PARAMETERS:\r\n");
            sb.Append("");

            // Recordset
            if (sp.RecordsetType.Length != 0)
            {
                sb.Append("//\t");
                sb.Append(RecordsetTypeMap[sp.RecordsetType]);
                sb.Append(" &rst");
                sb.Append("\r\n");
            }

            // Parameters
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);
                sb.Append("//\tSQLNAME:");
                sb.Append(param.SqlName);
                sb.Append("\tNAME:");
                sb.Append(param.Name);
                sb.Append("\tTYPE:");
                sb.Append(param.SqlType);
                sb.Append("\tDIRECTION:");
                sb.Append(param.SqlDirection);
                sb.Append("\tLENGTH:");
                sb.Append(param.SqlLen);
                sb.Append("\r\n");
            }
            // Ret
            sb.Append("// RETURN:");
            sb.Append(sp.Ret ? "int" : "void");
            sb.Append("\r\npublic ");

            // Function
            // Return
            sb.Append(sp.Ret ? "int" : "void");
            sb.Append(' ');

            // Name
            sb.Append(sp.Name);
            sb.Append('(');

            // Recordset
            if (sp.RecordsetType.Length != 0)
            {
                sb.Append("ref ");
                sb.Append(RecordsetTypeMap[sp.RecordsetType]);
                sb.Append(" rst");
                sb.Append(",");
            }

            // Parameter declarations
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);

                if (param.SqlDirection != "in")
                    sb.Append("ref ");
                sb.Append(ParamTypeMap[param.SqlType]);
                sb.Append(' ');
                sb.Append(param.Name);
                sb.Append(',');
            } 

            // Connection 
            if (bOutterConn)
                sb.Append("SqlConnection conn");
            else if (cnt != 0)
                sb.Remove(sb.Length - 1, 1);
            sb.Append(")\r\n{\r\n\t");

            // function
            string strConn = (bOutterConn ? "conn" : "m_conn");

            sb.Append("SqlCommand cmd = new SqlCommand(\"");
            sb.Append(sp.Name);
            sb.Append("\",");
            sb.Append(strConn);
            sb.Append(");\r\n");
	        sb.Append("\tcmd.CommandType=CommandType.StoredProcedure;\r\n");
            if (bShortConn)
            {
                sb.Append('\t');
                sb.Append(strConn);
                sb.Append(".Open();\r\n");
            }


            // Input
            // Stored procedure parameters
            string strParamName;
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);
                if (param.SqlDirection == "in")
                {
                    // Add Parameter with sql name and value
                    sb.Append("\tcmd.Parameters.AddWithValue(\"");
                    sb.Append(param.SqlName);
                    sb.Append("\",");
                    sb.Append(param.Name);
                    sb.Append(");\r\n");
                }
                else if (param.SqlDirection == "out")
                {
                    // Add Parameter with sqlname,sqltype,length
                    strParamName = "param" + param.Name;
                    sb.Append("\tSqlParameter ");
                    sb.Append(strParamName);
                    sb.Append(" = ");
                    sb.Append("cmd.Parameters.Add(\"");
                    sb.Append(param.SqlName);
                    sb.Append("\",");
                    sb.Append(ParamDBTypeMap[param.SqlType]);
                    sb.Append(',');
                    sb.Append(param.SqlLen.ToString());
                    sb.Append(");\r\n\t");

                    // Direction
                    sb.Append(strParamName);
                    sb.Append(".Direction = ParameterDirection.Output;\r\n");
                }
                else // if (param.SqlDirection == "inout")
                {
                    // Add Parameter with sqlname,sqltype,length
                    strParamName = "param" + param.Name;
                    sb.Append("\tSqlParameter ");
                    sb.Append(strParamName);
                    sb.Append(" = ");
                    sb.Append("cmd.Parameters.Add(\"");
                    sb.Append(param.SqlName);
                    sb.Append("\",");
                    sb.Append(ParamDBTypeMap[param.SqlType]);
                    sb.Append(',');
                    sb.Append(param.SqlLen.ToString());
                    sb.Append(");\r\n\t");

                    // Direction
                    sb.Append(strParamName);
                    sb.Append(".Direction = ParameterDirection.Output;\r\n\t");

                    // Value
                    sb.Append(strParamName);
                    sb.Append(".Value = ");
                    sb.Append(param.Name);
                    sb.Append(";\r\n");
                }
            }
            sb.Append('\t');
            // Return
            if (sp.Ret)
            {
                sb.Append("SqlParameter paramRetValue = cmd.Parameters.Add(\"@RetValue\",SqlDbType.Int);\r\n\t");
                sb.Append("paramRetValue.Direction = ParameterDirection.ReturnValue;\r\n\t");
            }


            // Execute 
            if (sp.RecordsetType.Length == 0)
            {
                sb.Append("cmd.ExecuteNonQuery();\r\n");
            }
            else if (sp.RecordsetType == "RECORDSET")
            { 
                sb.Append("rst = cmd.ExecuteReader();\r\n");
            }
            else
            {
                sb.Append("rst = (");
                sb.Append(RecordsetTypeMap[sp.RecordsetType]);
                sb.Append(")cmd.ExecuteScalar();\r\n");
            }
            // Output
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);
                if (param.SqlDirection != "in")
                {
                    sb.Append('\t');
                    sb.Append(param.Name);
                    sb.Append(" = (");
                    sb.Append(ParamTypeMap[param.SqlType]);
                    
                    strParamName = ")param" + param.Name;
                    sb.Append(strParamName);
                    sb.Append(".Value;\r\n");
                }
            }

            if (bShortConn && sp.RecordsetType != "RECORDSET")
            {
                sb.Append('\t');
                sb.Append(strConn);
                sb.Append(".Close();\r\n");
            }

            if (sp.RecordsetType == "RECORDSET")
            {
                sb.Append("\treturn reader;\r\n");
            }
            else if (sp.RecordsetType == "RET")
            {
                sb.Append("\treturn (int)paramRetValue.Value;\r\n");
            }
            else if (sp.RecordsetType != "VOID")
            {
                sb.Append("\treturn paramRetValue.Value;\r\n");
            }

            sb.Append("}\r\n\r\n\r\n");
            return sb.ToString();
        }

    };
}
