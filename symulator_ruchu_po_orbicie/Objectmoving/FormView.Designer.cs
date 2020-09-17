namespace Objectmoving
{
    partial class FormView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormView));
            this.tmrMoving = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.hScrollBar2 = new System.Windows.Forms.HScrollBar();
            this.label3 = new System.Windows.Forms.Label();
            this.hScrollBar3 = new System.Windows.Forms.HScrollBar();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Vy_Value = new System.Windows.Forms.Label();
            this.Vy = new System.Windows.Forms.Label();
            this.Vx_Value = new System.Windows.Forms.Label();
            this.Vx = new System.Windows.Forms.Label();
            this.velocity_value = new System.Windows.Forms.Label();
            this.Velocity = new System.Windows.Forms.Label();
            this.okres_value = new System.Windows.Forms.Label();
            this.okres = new System.Windows.Forms.Label();
            this.PolosValue = new System.Windows.Forms.Label();
            this.Polos = new System.Windows.Forms.Label();
            this.anomaliaprawdziwavalue = new System.Windows.Forms.Label();
            this.anomaliaprawdziwatext = new System.Windows.Forms.Label();
            this.pedegriee_value = new System.Windows.Forms.Label();
            this.apogee_value = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.hScrollBar4 = new System.Windows.Forms.HScrollBar();
            this.current_time = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.ascnode = new System.Windows.Forms.Label();
            this.inklinacja = new System.Windows.Forms.Label();
            this.mimosrud = new System.Windows.Forms.Label();
            this.promień = new System.Windows.Forms.Label();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tmrMoving
            // 
            this.tmrMoving.Enabled = true;
            this.tmrMoving.Interval = 1;
            this.tmrMoving.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.ForeColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Lime;
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // hScrollBar1
            // 
            resources.ApplyResources(this.hScrollBar1, "hScrollBar1");
            this.hScrollBar1.Maximum = 371;
            this.hScrollBar1.Minimum = -361;
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.SmallChange = 5;
            this.hScrollBar1.ValueChanged += new System.EventHandler(this.hScrollBar1_ValueChanged);
            this.hScrollBar1.CausesValidationChanged += new System.EventHandler(this.Form1_Load);
            this.hScrollBar1.RightToLeftChanged += new System.EventHandler(this.Form1_Load);
            this.hScrollBar1.DragEnter += new System.Windows.Forms.DragEventHandler(this.hScrollBar1_DragEnter);
            // 
            // hScrollBar2
            // 
            resources.ApplyResources(this.hScrollBar2, "hScrollBar2");
            this.hScrollBar2.Maximum = 372;
            this.hScrollBar2.Minimum = -362;
            this.hScrollBar2.Name = "hScrollBar2";
            this.hScrollBar2.SmallChange = 5;
            this.hScrollBar2.ValueChanged += new System.EventHandler(this.hScrollBar2_ValueChanged);
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Cyan;
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // hScrollBar3
            // 
            resources.ApplyResources(this.hScrollBar3, "hScrollBar3");
            this.hScrollBar3.Maximum = 372;
            this.hScrollBar3.Minimum = -362;
            this.hScrollBar3.Name = "hScrollBar3";
            this.hScrollBar3.SmallChange = 5;
            this.hScrollBar3.ValueChanged += new System.EventHandler(this.hScrollBar3_ValueChanged);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.textBox10);
            this.panel1.Controls.Add(this.textBox9);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.textBox8);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.Vy_Value);
            this.panel1.Controls.Add(this.Vy);
            this.panel1.Controls.Add(this.Vx_Value);
            this.panel1.Controls.Add(this.Vx);
            this.panel1.Controls.Add(this.velocity_value);
            this.panel1.Controls.Add(this.Velocity);
            this.panel1.Controls.Add(this.okres_value);
            this.panel1.Controls.Add(this.okres);
            this.panel1.Controls.Add(this.PolosValue);
            this.panel1.Controls.Add(this.Polos);
            this.panel1.Controls.Add(this.anomaliaprawdziwavalue);
            this.panel1.Controls.Add(this.anomaliaprawdziwatext);
            this.panel1.Controls.Add(this.pedegriee_value);
            this.panel1.Controls.Add(this.apogee_value);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.hScrollBar4);
            this.panel1.Controls.Add(this.current_time);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.textBox7);
            this.panel1.Controls.Add(this.textBox6);
            this.panel1.Controls.Add(this.textBox5);
            this.panel1.Controls.Add(this.textBox4);
            this.panel1.Controls.Add(this.textBox3);
            this.panel1.Controls.Add(this.textBox2);
            this.panel1.Controls.Add(this.textBox1);
            this.panel1.Controls.Add(this.ascnode);
            this.panel1.Controls.Add(this.inklinacja);
            this.panel1.Controls.Add(this.mimosrud);
            this.panel1.Controls.Add(this.promień);
            this.panel1.Controls.Add(this.hScrollBar1);
            this.panel1.Controls.Add(this.hScrollBar2);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.hScrollBar3);
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Name = "panel1";
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label9
            // 
            resources.ApplyResources(this.label9, "label9");
            this.label9.Name = "label9";
            // 
            // label8
            // 
            resources.ApplyResources(this.label8, "label8");
            this.label8.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label8.Name = "label8";
            // 
            // textBox10
            // 
            resources.ApplyResources(this.textBox10, "textBox10");
            this.textBox10.Name = "textBox10";
            this.textBox10.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox10_KeyPress);
            // 
            // textBox9
            // 
            resources.ApplyResources(this.textBox9, "textBox9");
            this.textBox9.Name = "textBox9";
            this.textBox9.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox9_KeyPress);
            // 
            // label7
            // 
            resources.ApplyResources(this.label7, "label7");
            this.label7.Name = "label7";
            // 
            // textBox8
            // 
            resources.ApplyResources(this.textBox8, "textBox8");
            this.textBox8.Name = "textBox8";
            this.textBox8.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox8_KeyDown);
            this.textBox8.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox8_KeyPress);
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // Vy_Value
            // 
            resources.ApplyResources(this.Vy_Value, "Vy_Value");
            this.Vy_Value.Name = "Vy_Value";
            // 
            // Vy
            // 
            resources.ApplyResources(this.Vy, "Vy");
            this.Vy.Name = "Vy";
            // 
            // Vx_Value
            // 
            resources.ApplyResources(this.Vx_Value, "Vx_Value");
            this.Vx_Value.Name = "Vx_Value";
            // 
            // Vx
            // 
            resources.ApplyResources(this.Vx, "Vx");
            this.Vx.Name = "Vx";
            // 
            // velocity_value
            // 
            resources.ApplyResources(this.velocity_value, "velocity_value");
            this.velocity_value.Name = "velocity_value";
            // 
            // Velocity
            // 
            resources.ApplyResources(this.Velocity, "Velocity");
            this.Velocity.Name = "Velocity";
            // 
            // okres_value
            // 
            resources.ApplyResources(this.okres_value, "okres_value");
            this.okres_value.Name = "okres_value";
            // 
            // okres
            // 
            resources.ApplyResources(this.okres, "okres");
            this.okres.Name = "okres";
            // 
            // PolosValue
            // 
            resources.ApplyResources(this.PolosValue, "PolosValue");
            this.PolosValue.Name = "PolosValue";
            // 
            // Polos
            // 
            resources.ApplyResources(this.Polos, "Polos");
            this.Polos.Name = "Polos";
            // 
            // anomaliaprawdziwavalue
            // 
            resources.ApplyResources(this.anomaliaprawdziwavalue, "anomaliaprawdziwavalue");
            this.anomaliaprawdziwavalue.Name = "anomaliaprawdziwavalue";
            // 
            // anomaliaprawdziwatext
            // 
            resources.ApplyResources(this.anomaliaprawdziwatext, "anomaliaprawdziwatext");
            this.anomaliaprawdziwatext.Name = "anomaliaprawdziwatext";
            // 
            // pedegriee_value
            // 
            resources.ApplyResources(this.pedegriee_value, "pedegriee_value");
            this.pedegriee_value.Name = "pedegriee_value";
            // 
            // apogee_value
            // 
            resources.ApplyResources(this.apogee_value, "apogee_value");
            this.apogee_value.Name = "apogee_value";
            // 
            // label11
            // 
            resources.ApplyResources(this.label11, "label11");
            this.label11.Name = "label11";
            // 
            // label10
            // 
            resources.ApplyResources(this.label10, "label10");
            this.label10.Name = "label10";
            // 
            // label6
            // 
            resources.ApplyResources(this.label6, "label6");
            this.label6.Name = "label6";
            // 
            // hScrollBar4
            // 
            this.hScrollBar4.LargeChange = 1;
            resources.ApplyResources(this.hScrollBar4, "hScrollBar4");
            this.hScrollBar4.Maximum = 5;
            this.hScrollBar4.Minimum = -2;
            this.hScrollBar4.Name = "hScrollBar4";
            this.hScrollBar4.Value = -2;
            this.hScrollBar4.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar4_Scroll);
            // 
            // current_time
            // 
            resources.ApplyResources(this.current_time, "current_time");
            this.current_time.Name = "current_time";
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // textBox7
            // 
            resources.ApplyResources(this.textBox7, "textBox7");
            this.textBox7.Name = "textBox7";
            this.textBox7.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox7_KeyPress);
            // 
            // textBox6
            // 
            resources.ApplyResources(this.textBox6, "textBox6");
            this.textBox6.Name = "textBox6";
            this.textBox6.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox6_KeyPress);
            // 
            // textBox5
            // 
            this.textBox5.AcceptsReturn = true;
            resources.ApplyResources(this.textBox5, "textBox5");
            this.textBox5.Name = "textBox5";
            this.textBox5.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox5_KeyPress);
            // 
            // textBox4
            // 
            resources.ApplyResources(this.textBox4, "textBox4");
            this.textBox4.Name = "textBox4";
            this.textBox4.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox4_KeyPress);
            // 
            // textBox3
            // 
            resources.ApplyResources(this.textBox3, "textBox3");
            this.textBox3.Name = "textBox3";
            this.textBox3.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox3_KeyPress);
            // 
            // textBox2
            // 
            resources.ApplyResources(this.textBox2, "textBox2");
            this.textBox2.Name = "textBox2";
            this.textBox2.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox2_KeyPress);
            // 
            // textBox1
            // 
            resources.ApplyResources(this.textBox1, "textBox1");
            this.textBox1.Name = "textBox1";
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // ascnode
            // 
            resources.ApplyResources(this.ascnode, "ascnode");
            this.ascnode.Name = "ascnode";
            this.ascnode.UseCompatibleTextRendering = true;
            // 
            // inklinacja
            // 
            resources.ApplyResources(this.inklinacja, "inklinacja");
            this.inklinacja.Name = "inklinacja";
            // 
            // mimosrud
            // 
            resources.ApplyResources(this.mimosrud, "mimosrud");
            this.mimosrud.Name = "mimosrud";
            // 
            // promień
            // 
            resources.ApplyResources(this.promień, "promień");
            this.promień.Name = "promień";
            // 
            // FormView
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.panel1);
            this.DoubleBuffered = true;
            this.Name = "FormView";
            this.Load += new System.EventHandler(this.FormView_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.SQUARE);
            this.Resize += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer tmrMoving;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.HScrollBar hScrollBar2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.HScrollBar hScrollBar3;
        public System.Windows.Forms.HScrollBar hScrollBar1;
        public System.Windows.Forms.Label label1;
       
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label promień;
        private System.Windows.Forms.Label mimosrud;
        private System.Windows.Forms.Label inklinacja;
        private System.Windows.Forms.Label ascnode;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        public System.Windows.Forms.TextBox textBox7;
        public System.Windows.Forms.TextBox textBox6;
        public System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Label current_time;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.HScrollBar hScrollBar4;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        public System.Windows.Forms.Label pedegriee_value;
        public System.Windows.Forms.Label apogee_value;
        public System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Label anomaliaprawdziwavalue;
        private System.Windows.Forms.Label anomaliaprawdziwatext;
        private System.Windows.Forms.Label Polos;
        public System.Windows.Forms.Label PolosValue;
        private System.Windows.Forms.Label okres_value;
        private System.Windows.Forms.Label okres;
        private System.Windows.Forms.Label velocity_value;
        private System.Windows.Forms.Label Velocity;
        private System.Windows.Forms.Label Vy_Value;
        private System.Windows.Forms.Label Vy;
        private System.Windows.Forms.Label Vx_Value;
        private System.Windows.Forms.Label Vx;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button1;
  
    //    private System.Windows.Forms.TrackBar trackBar1;

    }
}

  /*       this.hScrollBar1.Location = new System.Drawing.Point((this.ClientSize.Width - 95), 9);
            this.hScrollBar2.Location = new System.Drawing.Point((this.ClientSize.Width - 95), 34);
            this.hScrollBar3.Location = new System.Drawing.Point((this.ClientSize.Width - 95), 59);
            this.label1.Location = new System.Drawing.Point(this.ClientSize.Width - 115, 9);
            this.label2.Location = new System.Drawing.Point(this.ClientSize.Width - 115, 34);
            this.label3.Location = new System.Drawing.Point(this.ClientSize.Width - 115, 59);*/