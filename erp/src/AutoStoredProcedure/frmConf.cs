using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AutoStoredProcedure
{
    public partial class frmConf : Form
    {
        public frmConf()
        {
            InitializeComponent();
        }
 

        private void btnOK_Click(object sender, EventArgs e)
        {
            txtHost.Text = txtHost.Text.Trim();
            txtDB.Text = txtDB.Text.Trim();
            txtUser.Text = txtUser.Text.Trim();

            if (txtHost.Text.Trim().Length == 0)
            {
                txtHost.Select();
                txtHost.SelectAll();
            }
            else if (txtDB.Text.Trim().Length == 0)
            {
                txtDB.Select();
                txtDB.SelectAll();
            }
            else
            {
                Close();
                DialogResult = DialogResult.OK;
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
            DialogResult = DialogResult.Cancel;
        }
    }
}