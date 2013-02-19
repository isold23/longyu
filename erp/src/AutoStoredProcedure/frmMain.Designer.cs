namespace AutoStoredProcedure
{
    partial class frmMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.barTool = new System.Windows.Forms.ToolStrip();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.btnConn = new System.Windows.Forms.ToolStripButton();
            this.btnStart = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.btnSave = new System.Windows.Forms.ToolStripButton();
            this.btnCopy = new System.Windows.Forms.ToolStripButton();
            this.btnAbout = new System.Windows.Forms.ToolStripButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rd2000 = new System.Windows.Forms.RadioButton();
            this.rd2005 = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.ckShortConn = new System.Windows.Forms.CheckBox();
            this.ckOutterConn = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rdCSharp = new System.Windows.Forms.RadioButton();
            this.rdVC = new System.Windows.Forms.RadioButton();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.barStatus = new System.Windows.Forms.StatusStrip();
            this.txtStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnConf = new System.Windows.Forms.Button();
            this.txtConn = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.splitter2 = new System.Windows.Forms.Splitter();
            this.gvSP = new System.Windows.Forms.DataGridView();
            this.NameCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RecordsetCol = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.RetCol = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.CreateCol = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.txtClass = new System.Windows.Forms.TextBox();
            this.menuMain = new System.Windows.Forms.MenuStrip();
            this.miFile = new System.Windows.Forms.ToolStripMenuItem();
            this.miConn = new System.Windows.Forms.ToolStripMenuItem();
            this.miStart = new System.Windows.Forms.ToolStripMenuItem();
            this.miSave = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.miExit = new System.Windows.Forms.ToolStripMenuItem();
            this.miHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.miAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.dlgSaveFile = new System.Windows.Forms.SaveFileDialog();
            this.barTool.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.barStatus.SuspendLayout();
            this.panel1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gvSP)).BeginInit();
            this.menuMain.SuspendLayout();
            this.SuspendLayout();
            // 
            // barTool
            // 
            this.barTool.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripSeparator2,
            this.btnConn,
            this.btnStart,
            this.toolStripSeparator1,
            this.btnSave,
            this.btnCopy,
            this.btnAbout});
            this.barTool.Location = new System.Drawing.Point(0, 25);
            this.barTool.Name = "barTool";
            this.barTool.Size = new System.Drawing.Size(960, 25);
            this.barTool.TabIndex = 0;
            this.barTool.Text = "工具栏";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // btnConn
            // 
            this.btnConn.Image = ((System.Drawing.Image)(resources.GetObject("btnConn.Image")));
            this.btnConn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnConn.Name = "btnConn";
            this.btnConn.Size = new System.Drawing.Size(70, 22);
            this.btnConn.Text = "连接(&N)";
            this.btnConn.ToolTipText = "连接到数据库并显示所有用户存储过程";
            this.btnConn.Click += new System.EventHandler(this.btnConn_Click);
            // 
            // btnStart
            // 
            this.btnStart.Image = ((System.Drawing.Image)(resources.GetObject("btnStart.Image")));
            this.btnStart.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(69, 22);
            this.btnStart.Text = "开始(&G)";
            this.btnStart.ToolTipText = "开始生成相应的存储过程及类代码";
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // btnSave
            // 
            this.btnSave.Image = ((System.Drawing.Image)(resources.GetObject("btnSave.Image")));
            this.btnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(67, 22);
            this.btnSave.Text = "保存(&S)";
            this.btnSave.ToolTipText = "将生成保存到指定文件";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnCopy
            // 
            this.btnCopy.Image = ((System.Drawing.Image)(resources.GetObject("btnCopy.Image")));
            this.btnCopy.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.Size = new System.Drawing.Size(68, 22);
            this.btnCopy.Text = "复制(&C)";
            this.btnCopy.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnCopy.ToolTipText = "复制到剪贴板";
            this.btnCopy.Click += new System.EventHandler(this.btnCopy_Click);
            // 
            // btnAbout
            // 
            this.btnAbout.Image = ((System.Drawing.Image)(resources.GetObject("btnAbout.Image")));
            this.btnAbout.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnAbout.Name = "btnAbout";
            this.btnAbout.Size = new System.Drawing.Size(68, 22);
            this.btnAbout.Text = "关于(&A)";
            this.btnAbout.Click += new System.EventHandler(this.btnAbout_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rd2000);
            this.groupBox3.Controls.Add(this.rd2005);
            this.groupBox3.Location = new System.Drawing.Point(9, 117);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(135, 69);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "MS数据库";
            // 
            // rd2000
            // 
            this.rd2000.AutoSize = true;
            this.rd2000.Checked = true;
            this.rd2000.Location = new System.Drawing.Point(16, 20);
            this.rd2000.Name = "rd2000";
            this.rd2000.Size = new System.Drawing.Size(113, 16);
            this.rd2000.TabIndex = 7;
            this.rd2000.TabStop = true;
            this.rd2000.Text = "SQL SERVER 2000";
            this.rd2000.UseVisualStyleBackColor = true;
            this.rd2000.CheckedChanged += new System.EventHandler(this.ck_CheckedChanged);
            // 
            // rd2005
            // 
            this.rd2005.AutoSize = true;
            this.rd2005.Location = new System.Drawing.Point(16, 42);
            this.rd2005.Name = "rd2005";
            this.rd2005.Size = new System.Drawing.Size(113, 16);
            this.rd2005.TabIndex = 6;
            this.rd2005.Text = "SQL SERVER 2005";
            this.rd2005.UseVisualStyleBackColor = true;
            this.rd2005.CheckedChanged += new System.EventHandler(this.ck_CheckedChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ckShortConn);
            this.groupBox2.Controls.Add(this.ckOutterConn);
            this.groupBox2.Location = new System.Drawing.Point(9, 212);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(135, 71);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "连接";
            // 
            // ckShortConn
            // 
            this.ckShortConn.AutoSize = true;
            this.ckShortConn.Location = new System.Drawing.Point(24, 44);
            this.ckShortConn.Name = "ckShortConn";
            this.ckShortConn.Size = new System.Drawing.Size(60, 16);
            this.ckShortConn.TabIndex = 9;
            this.ckShortConn.Text = "短连接";
            this.ckShortConn.UseVisualStyleBackColor = true;
            // 
            // ckOutterConn
            // 
            this.ckOutterConn.AutoSize = true;
            this.ckOutterConn.Location = new System.Drawing.Point(24, 21);
            this.ckOutterConn.Name = "ckOutterConn";
            this.ckOutterConn.Size = new System.Drawing.Size(72, 16);
            this.ckOutterConn.TabIndex = 8;
            this.ckOutterConn.Text = "外部连接";
            this.ckOutterConn.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rdCSharp);
            this.groupBox1.Controls.Add(this.rdVC);
            this.groupBox1.Location = new System.Drawing.Point(9, 22);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(135, 69);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "语言";
            // 
            // rdCSharp
            // 
            this.rdCSharp.AutoSize = true;
            this.rdCSharp.Location = new System.Drawing.Point(16, 25);
            this.rdCSharp.Name = "rdCSharp";
            this.rdCSharp.Size = new System.Drawing.Size(35, 16);
            this.rdCSharp.TabIndex = 7;
            this.rdCSharp.Text = "C#";
            this.rdCSharp.UseVisualStyleBackColor = true;
            this.rdCSharp.CheckedChanged += new System.EventHandler(this.ck_CheckedChanged);
            // 
            // rdVC
            // 
            this.rdVC.AutoSize = true;
            this.rdVC.Checked = true;
            this.rdVC.Location = new System.Drawing.Point(16, 47);
            this.rdVC.Name = "rdVC";
            this.rdVC.Size = new System.Drawing.Size(47, 16);
            this.rdVC.TabIndex = 6;
            this.rdVC.TabStop = true;
            this.rdVC.Text = "VC++";
            this.rdVC.UseVisualStyleBackColor = true;
            this.rdVC.CheckedChanged += new System.EventHandler(this.ck_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Red;
            this.label5.Location = new System.Drawing.Point(12, 75);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(119, 12);
            this.label5.TabIndex = 0;
            this.label5.Text = "或外连接Close()函数";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(12, 56);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(101, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "调用Finish()函数";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(14, 38);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(101, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "查询返回外部需要";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Red;
            this.label2.Location = new System.Drawing.Point(12, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(119, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "当短连接返回记录时,";
            // 
            // barStatus
            // 
            this.barStatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.txtStatus});
            this.barStatus.Location = new System.Drawing.Point(0, 482);
            this.barStatus.Name = "barStatus";
            this.barStatus.Size = new System.Drawing.Size(807, 22);
            this.barStatus.TabIndex = 36;
            this.barStatus.Text = "statusStrip1";
            // 
            // txtStatus
            // 
            this.txtStatus.Name = "txtStatus";
            this.txtStatus.Size = new System.Drawing.Size(0, 17);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.btnConf);
            this.panel1.Controls.Add(this.txtConn);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 50);
            this.panel1.MinimumSize = new System.Drawing.Size(800, 0);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(5, 10, 5, 5);
            this.panel1.Size = new System.Drawing.Size(807, 38);
            this.panel1.TabIndex = 35;
            // 
            // btnConf
            // 
            this.btnConf.Dock = System.Windows.Forms.DockStyle.Right;
            this.btnConf.Location = new System.Drawing.Point(772, 10);
            this.btnConf.Name = "btnConf";
            this.btnConf.Size = new System.Drawing.Size(30, 23);
            this.btnConf.TabIndex = 11;
            this.btnConf.Text = "...";
            this.btnConf.UseVisualStyleBackColor = true;
            this.btnConf.Click += new System.EventHandler(this.btnConf_Click);
            // 
            // txtConn
            // 
            this.txtConn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtConn.Location = new System.Drawing.Point(115, 10);
            this.txtConn.Name = "txtConn";
            this.txtConn.Size = new System.Drawing.Size(687, 21);
            this.txtConn.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.Dock = System.Windows.Forms.DockStyle.Left;
            this.label1.Location = new System.Drawing.Point(5, 10);
            this.label1.Margin = new System.Windows.Forms.Padding(3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(110, 23);
            this.label1.TabIndex = 9;
            this.label1.Text = "数据库连接字符串";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.ForeColor = System.Drawing.Color.Red;
            this.groupBox4.Location = new System.Drawing.Point(9, 309);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(135, 99);
            this.groupBox4.TabIndex = 13;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "C#备注";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.groupBox4);
            this.panel2.Controls.Add(this.groupBox3);
            this.panel2.Controls.Add(this.groupBox2);
            this.panel2.Controls.Add(this.groupBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(807, 50);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(153, 454);
            this.panel2.TabIndex = 37;
            // 
            // splitter2
            // 
            this.splitter2.Location = new System.Drawing.Point(288, 88);
            this.splitter2.Name = "splitter2";
            this.splitter2.Size = new System.Drawing.Size(5, 394);
            this.splitter2.TabIndex = 44;
            this.splitter2.TabStop = false;
            // 
            // gvSP
            // 
            this.gvSP.AllowUserToAddRows = false;
            this.gvSP.AllowUserToResizeRows = false;
            this.gvSP.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gvSP.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NameCol,
            this.RecordsetCol,
            this.RetCol,
            this.CreateCol});
            this.gvSP.Dock = System.Windows.Forms.DockStyle.Left;
            this.gvSP.EditMode = System.Windows.Forms.DataGridViewEditMode.EditOnEnter;
            this.gvSP.Location = new System.Drawing.Point(0, 88);
            this.gvSP.MultiSelect = false;
            this.gvSP.Name = "gvSP";
            this.gvSP.RowHeadersVisible = false;
            this.gvSP.RowTemplate.Height = 23;
            this.gvSP.Size = new System.Drawing.Size(288, 394);
            this.gvSP.TabIndex = 43;
            this.gvSP.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.gvSP_ColumnHeaderMouseClick);
            // 
            // NameCol
            // 
            this.NameCol.HeaderText = "名称";
            this.NameCol.Name = "NameCol";
            this.NameCol.ReadOnly = true;
            this.NameCol.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.NameCol.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.NameCol.Width = 120;
            // 
            // RecordsetCol
            // 
            this.RecordsetCol.AutoComplete = false;
            this.RecordsetCol.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.Nothing;
            this.RecordsetCol.HeaderText = "结果集";
            this.RecordsetCol.Items.AddRange(new object[] {
            "",
            "INT64",
            "INT",
            "SHORT",
            "BYTE",
            "BOOL",
            "DOUBLE",
            "FLOAT",
            "DATETIME",
            "STRING",
            "RECORDSET"});
            this.RecordsetCol.MaxDropDownItems = 12;
            this.RecordsetCol.Name = "RecordsetCol";
            this.RecordsetCol.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.RecordsetCol.Width = 60;
            // 
            // RetCol
            // 
            this.RetCol.HeaderText = "返回";
            this.RetCol.Name = "RetCol";
            this.RetCol.Width = 50;
            // 
            // CreateCol
            // 
            this.CreateCol.HeaderText = "生成";
            this.CreateCol.Name = "CreateCol";
            this.CreateCol.Width = 50;
            // 
            // splitter1
            // 
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitter1.Location = new System.Drawing.Point(293, 360);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(514, 5);
            this.splitter1.TabIndex = 46;
            this.splitter1.TabStop = false;
            // 
            // txtClass
            // 
            this.txtClass.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.txtClass.Location = new System.Drawing.Point(293, 365);
            this.txtClass.MaxLength = 32767000;
            this.txtClass.Multiline = true;
            this.txtClass.Name = "txtClass";
            this.txtClass.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtClass.Size = new System.Drawing.Size(514, 117);
            this.txtClass.TabIndex = 45;
            // 
            // menuMain
            // 
            this.menuMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miFile,
            this.miHelp});
            this.menuMain.Location = new System.Drawing.Point(0, 0);
            this.menuMain.Name = "menuMain";
            this.menuMain.Size = new System.Drawing.Size(960, 25);
            this.menuMain.TabIndex = 47;
            this.menuMain.Text = "menuStrip1";
            // 
            // miFile
            // 
            this.miFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miConn,
            this.miStart,
            this.miSave,
            this.toolStripSeparator3,
            this.miExit});
            this.miFile.Name = "miFile";
            this.miFile.Size = new System.Drawing.Size(58, 21);
            this.miFile.Text = "文件(&F)";
            // 
            // miConn
            // 
            this.miConn.Name = "miConn";
            this.miConn.Size = new System.Drawing.Size(116, 22);
            this.miConn.Text = "连接(&C)";
            this.miConn.Click += new System.EventHandler(this.btnConn_Click);
            // 
            // miStart
            // 
            this.miStart.Name = "miStart";
            this.miStart.Size = new System.Drawing.Size(116, 22);
            this.miStart.Text = "生成&G)";
            this.miStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // miSave
            // 
            this.miSave.Name = "miSave";
            this.miSave.Size = new System.Drawing.Size(116, 22);
            this.miSave.Text = "保存(&S)";
            this.miSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(113, 6);
            // 
            // miExit
            // 
            this.miExit.Name = "miExit";
            this.miExit.Size = new System.Drawing.Size(116, 22);
            this.miExit.Text = "退出(&X)";
            this.miExit.Click += new System.EventHandler(this.miExit_Click);
            // 
            // miHelp
            // 
            this.miHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.miAbout});
            this.miHelp.Name = "miHelp";
            this.miHelp.Size = new System.Drawing.Size(61, 21);
            this.miHelp.Text = "帮助(&H)";
            // 
            // miAbout
            // 
            this.miAbout.Name = "miAbout";
            this.miAbout.Size = new System.Drawing.Size(116, 22);
            this.miAbout.Text = "关于(&A)";
            this.miAbout.Click += new System.EventHandler(this.btnAbout_Click);
            // 
            // txtOutput
            // 
            this.txtOutput.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtOutput.Location = new System.Drawing.Point(293, 88);
            this.txtOutput.MaxLength = 32767000;
            this.txtOutput.Multiline = true;
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtOutput.Size = new System.Drawing.Size(514, 272);
            this.txtOutput.TabIndex = 48;
            this.txtOutput.TextChanged += new System.EventHandler(this.txtOutput_TextChanged);
            // 
            // dlgSaveFile
            // 
            this.dlgSaveFile.DefaultExt = "txt";
            this.dlgSaveFile.Filter = "文本文件|.txt|所有文件|*.*";
            this.dlgSaveFile.Title = "保存";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(960, 504);
            this.Controls.Add(this.txtOutput);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.txtClass);
            this.Controls.Add(this.splitter2);
            this.Controls.Add(this.gvSP);
            this.Controls.Add(this.barStatus);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.barTool);
            this.Controls.Add(this.menuMain);
            this.MainMenuStrip = this.menuMain;
            this.MinimumSize = new System.Drawing.Size(803, 538);
            this.Name = "frmMain";
            this.Text = "存储过程调用代码生成";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.barTool.ResumeLayout(false);
            this.barTool.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.barStatus.ResumeLayout(false);
            this.barStatus.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.gvSP)).EndInit();
            this.menuMain.ResumeLayout(false);
            this.menuMain.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip barTool;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton rd2000;
        private System.Windows.Forms.RadioButton rd2005;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox ckShortConn;
        private System.Windows.Forms.CheckBox ckOutterConn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rdCSharp;
        private System.Windows.Forms.RadioButton rdVC;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.StatusStrip barStatus;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Splitter splitter2;
        private System.Windows.Forms.DataGridView gvSP;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.TextBox txtClass;
        private System.Windows.Forms.ToolStripButton btnConn;
        private System.Windows.Forms.MenuStrip menuMain;
        private System.Windows.Forms.ToolStripMenuItem miFile;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton btnStart;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton btnSave;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.SaveFileDialog dlgSaveFile;
        private System.Windows.Forms.ToolStripMenuItem miConn;
        private System.Windows.Forms.ToolStripMenuItem miStart;
        private System.Windows.Forms.ToolStripMenuItem miSave;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem miExit;
        private System.Windows.Forms.ToolStripMenuItem miHelp;
        private System.Windows.Forms.ToolStripMenuItem miAbout;
        private System.Windows.Forms.ToolStripButton btnAbout;
        private System.Windows.Forms.ToolStripStatusLabel txtStatus;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtConn;
        private System.Windows.Forms.Button btnConf;
        private System.Windows.Forms.DataGridViewTextBoxColumn NameCol;
        private System.Windows.Forms.DataGridViewComboBoxColumn RecordsetCol;
        private System.Windows.Forms.DataGridViewCheckBoxColumn RetCol;
        private System.Windows.Forms.DataGridViewCheckBoxColumn CreateCol;
        private System.Windows.Forms.ToolStripButton btnCopy;

    }
}

