using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.IO;

namespace AutoStoredProcedure
{
    public partial class frmMain : Form
    {
        SqlConnection m_conn;
        SPCreator m_activeCreator;
        DBProvider m_activeDBProvider;
        bool m_allSelected;
        public frmMain()
        {
            InitializeComponent();
            // txtConn.Text = "Data Source=localhost;Initial Catalog=Test;Integrated Security=True";
            txtConn.Text = "Data Source=WANGLIWEI-PC\\PROPMGR;Initial Catalog=Prop;Persist Security Info=True;User ID=sa;Password=sa";
            m_allSelected = false;
        
            if (this.rdVC.Checked)
                m_activeCreator  = VCSPCreator.Inst;
            else
                m_activeCreator  = CSharpSPCreator.Inst;

            if (this.rd2000.Checked)
                m_activeDBProvider = MSSql2000Provider.Inst;
            else
                m_activeDBProvider = MSSql2005Provider.Inst;

        }



        private void btnStart_Click(object sender, EventArgs e)
        {
            SqlDataReader reader = null;
            txtStatus.Text = "正在生成存储过程.......";
            try
            {
                SqlCommand cmd = new SqlCommand(m_activeDBProvider.ParamSql, m_conn);
                reader = cmd.ExecuteReader();

                DataTable dt = m_activeDBProvider.GetDataTable(reader);
 
                GenSP(dt, ckOutterConn.Checked, ckShortConn.Checked);
                txtOutput.Text = m_activeCreator.GenClassBegin(ckOutterConn.Checked, ckShortConn.Checked)
                    + GenSP(dt, ckOutterConn.Checked, ckShortConn.Checked) 
                    + m_activeCreator.GenClassEnd(ckOutterConn.Checked, ckShortConn.Checked);
               
                reader.Close();

                txtStatus.Text = "生成成功.";
            }
            catch (Exception ex)
            {
                if (reader != null)
                    reader.Close();

                txtStatus.Text = "生成失败!" + ex.Message;
            } 
        }
        //Data Source=192.168.2.108;Initial Catalog=DesktopPet_General;Persist Security Info=True;User ID=sa;Password=123
        private void btnConn_Click(object sender, EventArgs e)
        {
            txtStatus.Text = "正在连接数据库....";
            try
            {
                m_conn = new SqlConnection(txtConn.Text);
                m_conn.Open();

                gvSP.Rows.Clear();
                m_allSelected = false;
                SqlCommand cmd = new SqlCommand(m_activeDBProvider.SPSql, m_conn);
                SqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    string name = reader[0].ToString();
                    bool ret = (name[0] == 'r' || name[0] == 'R');
                    bool gen = (name[0] != '_');

                    string recordset;
                    switch (name[1])
                    {
                        /*recordset*/   case 'r': case 'R': recordset = "RECORDSET"; break;
                        /*logn*/        case 'l': case 'L': recordset = "INT64"; break;
                        /*int*/         case 'i': case 'I': recordset = "INT"; break;
                        /*short*/       case 's': case 'S': recordset = "SHORT"; break;
                        /*char*/        case 'c': case 'C': recordset = "BYTE"; break;
                        /*double*/      case 'd': case 'D': recordset = "DOUBLE"; break;
                        /*float*/       case 'f': case 'F': recordset = "FLOAT"; break;
                                        default: recordset =""; break;
                    }

                    object[] objs = { name, recordset, ret, gen };
                    int i = gvSP.Rows.Add(objs); 
                }
                reader.Close();

                txtStatus.Text = "连接成功.";
            }
            catch (Exception ex)
            {
                txtStatus.Text = "连接失败!";
                MessageBox.Show(ex.Message);
            }

        }


        private int ToSafeInt(object obj)
        {
            if (obj is DBNull)
                return 0;
            else
                return Convert.ToInt32((string)obj, 10);
        }

        private string GenSP(DataTable dt, bool bOutterConn, bool bShortConn)
        {
            const string STR_NOOP_SP = "未能找到对应存储过程的用户选项!";
            StoredProcedure sp = null;

            string strRet = "";
            string strSPName = "";
            string strRecordsetType = "";
            bool bRet = false;

            int i, cnt = dt.Rows.Count;

            for (i = 0; i < cnt; ++i)
            {
                DataRow row = dt.Rows[i];
                strSPName = (string)row["SPName"];
                //　新的存储过程
                if (sp == null)
                {
                    if (!UserOPSP(strSPName, ref strRecordsetType, ref bRet))
                        throw new System.Exception(STR_NOOP_SP);
                    sp = new StoredProcedure(strSPName, strRecordsetType, bRet);
                    sp.AddParam((string)row["ParamName"], (string)row["Type"], (string)row["Direction"], ToSafeInt(row["Len"]));
                }
                else
                {
                    // 老的存储过程 
                    if (sp.Name == strSPName)
                    {
                        sp.AddParam((string)row["ParamName"], (string)row["Type"], (string)row["Direction"], ToSafeInt(row["Len"]));
                    }
                    else
                    {
                        // 新的存储过程
                        // 处理已经完成的存储过程

                        if (UserOPSP(sp.Name))
                            strRet += m_activeCreator.Gen(sp, bOutterConn, bShortConn);

                        if (!UserOPSP(strSPName, ref strRecordsetType, ref bRet))
                            throw new System.Exception(STR_NOOP_SP);

                        sp = new StoredProcedure(strSPName, strRecordsetType, bRet);
                        sp.AddParam((string)row["ParamName"], (string)row["Type"], (string)row["Direction"], ToSafeInt(row["Len"]));
                    }
                }
            }

            if (sp != null && UserOPSP(sp.Name))
                strRet += m_activeCreator.Gen(sp, bOutterConn, bShortConn);

            return strRet;
        }

        private bool UserOPSP(string strSPName, ref string strRetType,ref bool bRet)
        {
            int i, cnt = gvSP.Rows.Count;
            for (i = 0; i < cnt; ++i)
                if ((string)gvSP.Rows[i].Cells[0].Value == strSPName)
                {
                    strRetType = (string)gvSP.Rows[i].Cells[1].Value;
                    bRet = (bool)gvSP.Rows[i].Cells[2].Value;
                    return true;
                }

            return false;
        }

        private bool UserOPSP(string strSPName)
        {
            int i, cnt = gvSP.Rows.Count;
            for (i = 0; i < cnt; ++i)
                if ((string)gvSP.Rows[i].Cells[0].Value == strSPName)
                    return (bool)gvSP.Rows[i].Cells[3].Value;

            return false;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (dlgSaveFile.ShowDialog() == DialogResult.OK)
            {
                StreamWriter sw = File.CreateText(dlgSaveFile.FileName);
                sw.Write(txtClass.Text);
                sw.Write(txtOutput.Text);
                sw.Close();
            }
        }

        private void ck_CheckedChanged(object sender, EventArgs e)
        {
            if (sender == rd2000)
            {
                m_activeDBProvider = MSSql2000Provider.Inst;
            }
            else if (sender == rd2005)
            {
                m_activeDBProvider = MSSql2005Provider.Inst;
            }
            else if (sender == rdCSharp)
            {
                m_activeCreator = CSharpSPCreator.Inst;
            }
            else if (sender == rdVC)
            {
                m_activeCreator = VCSPCreator.Inst;
            }
        }

        private void miExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void txtOutput_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnAbout_Click(object sender, EventArgs e)
        {
            frmAbout frm = new frmAbout();
            frm.ShowDialog(this);
        }

        private void btnConf_Click(object sender, EventArgs e)
        {
            frmConf frm = new frmConf();

            if (txtConn.Text.Trim().Length != 0)
            {
                string[] strs = txtConn.Text.Split(new char[]{';'});
                for (int i = 0; i < strs.Length; ++i)
                {
                    string[] substrs = strs[i].Split(new char[]{'='});
                    if (substrs.Length == 2)
                    {
                        string key = substrs[0].Trim().ToLower();
                        string val = substrs[1];
                        if (key == "data source")
                            frm.txtHost.Text = val.Trim();
                        else if (key == "initial catalog")
                            frm.txtDB.Text = val.Trim();
                        else if (key == "user id")
                            frm.txtUser.Text = val.Trim();
                        else if (key == "password")
                            frm.txtPwd.Text = val;
                    }
                }
            }
 
            frm.ShowDialog(this);
            if (frm.DialogResult == DialogResult.OK)
            {
                string str = "Data Source=";
                str += frm.txtHost.Text;
                str += ";Initial Catalog=";
                str += frm.txtDB.Text;

                if (frm.txtUser.Text.Length != 0)
                {
                    str += ";Persist Security Info=True;User ID=";
                    str += frm.txtUser.Text;
                    str += ";Password=";
                    str += frm.txtPwd.Text;
                }

                txtConn.Text = str;
            }
        }

        private void gvSP_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && (e.ColumnIndex == 2 || e.ColumnIndex == 3))
            {
                m_allSelected = !m_allSelected;
                for (int i = 0; i < gvSP.RowCount; ++i)
                    gvSP.Rows[i].Cells[e.ColumnIndex].Value = m_allSelected;
            }
        }

        private void btnCopy_Click(object sender, EventArgs e)
        {
            int start = txtOutput.SelectionStart;
            int len = txtOutput.SelectionLength;

            txtOutput.SelectAll();
            txtOutput.Copy();
            txtOutput.Select(start, len);
        }
 

    }
}