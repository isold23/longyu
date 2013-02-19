using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace AutoStoredProcedure
{
    public class VCSPCreator : SPCreator
    {
        public static VCSPCreator Inst = new VCSPCreator();

        private Hashtable m_mapParamAdoType = new Hashtable();

        protected Hashtable ParamAdoTypeMap
        {
            get { return m_mapParamAdoType; }
        }

        private VCSPCreator()
        {
            RecordsetTypeMap["INT64"] = "__int64";
            RecordsetTypeMap["INT"] = "int";
            RecordsetTypeMap["SHORT"] = "short";
            RecordsetTypeMap["BYTE"] = "char";
            RecordsetTypeMap["BOOL"] = "bool";
            RecordsetTypeMap["DOUBLE"] = "double";
            RecordsetTypeMap["FLOAT"] = "float";
            RecordsetTypeMap["DATETIME"] = "COleDateTime";
            RecordsetTypeMap["STRING"] = "CString";
            RecordsetTypeMap["RECORDSET"] = "_RecordsetPtr";

            ParamTypeMap["nvarchar"] = "CString";
            ParamTypeMap["varchar"] = "CString";
            ParamTypeMap["nchar"] = "CString";
            ParamTypeMap["char"] = "CString"; 
            ParamTypeMap["bit"] = "bool";
            ParamTypeMap["tinyint"] = "char";
            ParamTypeMap["smallint"] = "short";
            ParamTypeMap["int"] = "int";
            ParamTypeMap["bigint"] = "__int64";
            ParamTypeMap["float"] = "double";
            ParamTypeMap["decimal"] = "float";
            ParamTypeMap["real"] = "float";
            ParamTypeMap["datetime"] = "COleDateTime";

            ParamDBTypeMap["nvarchar"] = "SqlDbType.NVarchar";
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

            ParamAdoTypeMap["nvarchar"] = "adVarWChar";
            ParamAdoTypeMap["varchar"] = "adVarChar";
            ParamAdoTypeMap["nchar"] = "adWChar";
            ParamAdoTypeMap["char"] = "adChar"; 
            ParamAdoTypeMap["bit"] = "adBoolean";
            ParamAdoTypeMap["tinyint"] = "adTinyInt";
            ParamAdoTypeMap["smallint"] = "adSmallInt";
            ParamAdoTypeMap["int"] = "adInteger";
            ParamAdoTypeMap["bigint"] = "adBigInt";
            ParamAdoTypeMap["float"] = "adDouble";
            ParamAdoTypeMap["decimal"] = "adSingle";
            ParamAdoTypeMap["real"] = "adSingle";
            ParamAdoTypeMap["datetime"] = "adDate";
 
        }

        public override string GenClassBegin(bool bOutterConn, bool bShortConn)
        {
            return ("#ifndef ____sql_sp_call_impl\r\n#error \"sp.h must be included ____sql_sp_call_impl!!!!\r\n#else\r\n\r\n\r\n");            
        }

        public override string GenClassEnd(bool bOutterConn, bool bShortConn)
        {
            return "#endif";
        }

        private string GetAdoParamDirection(string strDirection)
        {
            if (strDirection == "in")
                return "adParamInput";
            else if (strDirection == "out")
                return "adParamOutput";
            else // if (strDirection == "inout")
                return "adParamInputOutput";
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
            sb.Append("\r\n");

            // inline
            // Function
            // Return
            sb.Append("inline ");
            sb.Append(sp.Ret ? "int" : "void");
            sb.Append(' ');

            // Name
            sb.Append(sp.Name);
            sb.Append('(');

            // Recordset
            if (sp.RecordsetType.Length != 0)
            {
                sb.Append(RecordsetTypeMap[sp.RecordsetType]);
                sb.Append(" &rst");
                sb.Append(",");
            }

            // Parameter declarations
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);

                sb.Append(ParamTypeMap[param.SqlType]);
                sb.Append(' ');
                if (param.SqlDirection != "in")
                    sb.Append("&");
                sb.Append(param.Name);
                sb.Append(',');
            }

            // Connection 
            if (bOutterConn)
                sb.Append("_ConnectionPtr &conn");
            else if (cnt != 0)
                sb.Remove(sb.Length - 1, 1);
            sb.Append(")\r\n{\r\n____sql_sp_call_try_begin\r\n\t");

            // function
            string strConn = (bOutterConn ? "conn" : "m_conn");

            sb.Append("_CommandPtr cmd(__uuidof(Command));\r\n\t");
            sb.Append("cmd->CommandText = L\"");
            sb.Append(sp.Name);
            sb.Append("\";\r\n\t");

            sb.Append("cmd->ActiveConnection = ");
            sb.Append(strConn);
            sb.Append(";\r\n");
            sb.Append("\tcmd->CommandType = adCmdStoredProc;\r\n");
            if (bShortConn)
            {
                sb.Append('\t');
                sb.Append(strConn);
                sb.Append("->Open();\r\n");
            }
            sb.Append('\t');

            // Return
            if (sp.Ret)
            {
                sb.Append("_ParameterPtr paramRetValue = cmd->CreateParameter(\"@RetValue\",adInteger,adParamReturnValue,4);\r\n\t");
                sb.Append("cmd->Parameters->Append(paramRetValue);\r\n\t");
            }
             
            // Stored procedure parameters
            string strParamName;
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);

                sb.Append("_ParameterPtr ");
                strParamName = "param" + param.Name;
                sb.Append(strParamName);
                sb.Append(" = cmd->CreateParameter(L\"");
                sb.Append(param.SqlName);
                sb.Append("\",");
                sb.Append(ParamAdoTypeMap[param.SqlType]);
                sb.Append(',');
                sb.Append(GetAdoParamDirection(param.SqlDirection));
                sb.Append(',');
                sb.Append(param.SqlLen.ToString());
                sb.Append(',');
                if (param.SqlDirection == "out")
                    sb.Append("VT_NULL");
                else
                {
                    sb.Append(param.Name);

                    object paramType = ParamTypeMap[param.SqlType];
                    string str = paramType.ToString();
                    if (str == "CString")
                        sb.Append(".GetString()");
                    else if (str == "COleDateTime")
                        sb.Append(".m_dt");

                }

                sb.Append(");\r\n\tcmd->Parameters->Append(");
                sb.Append(strParamName);
                sb.Append(");\r\n\t");
            }

            // Execute 
            if (sp.RecordsetType.Length == 0)
                sb.Append("cmd->Execute(NULL,NULL,adCmdStoredProc);\r\n");
            else if (sp.RecordsetType == "RECORDSET")
                sb.Append("rst = cmd->Execute(NULL,NULL,adCmdStoredProc);\r\n");
            else
                sb.Append("_RecordsetPtr rstSp = cmd->Execute(NULL,NULL,adCmdStoredProc);\r\n");


            // Output
            for (i = 0; i < cnt; ++i)
            {
                param = sp.ParamAt(i);
                if (param.SqlDirection != "in")
                {
                    sb.Append("\tif (param" + param.Name + "->Value.vt != VT_NULL) ");
                    sb.Append(param.Name);
                    sb.Append(" = (");
                    sb.Append(ParamTypeMap[param.SqlType]);

                    strParamName = ")param" + param.Name;
                    sb.Append(strParamName);
                    sb.Append("->Value;\r\n");
                }
            }

            if (bShortConn && sp.RecordsetType != "RECORDSET")
            {
                sb.Append('\t');
                sb.Append(strConn);
                sb.Append(".Close();\r\n");
            }

            if (sp.RecordsetType.Length != 0)
            {
                if (sp.RecordsetType != "RECORDSET")
                {
                    sb.Append("\trst = (");
                    sb.Append(RecordsetTypeMap[sp.RecordsetType]);
                    sb.Append(")rstSp->Fields[0]->Value;\r\n");
                }
            }

            if (sp.Ret)
            {
                sb.Append("\treturn (int)paramRetValue->Value;\r\n");
            }

            sb.Append("____sql_sp_call_catch\r\n");
            if (sp.Ret)
                sb.Append("\treturn ____sql_sp_call_errflag;\r\n");
            sb.Append("____sql_sp_call_end\r\n");
            sb.Append("}\r\n\r\n\r\n");
            return sb.ToString();
        }
    }
}
