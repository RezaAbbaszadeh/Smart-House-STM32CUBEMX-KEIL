namespace SmartHouse
{
	partial class Form1
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
			this.currentPass = new System.Windows.Forms.TextBox();
			this.changePass = new System.Windows.Forms.Button();
			this.datebtn = new System.Windows.Forms.Button();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.logBox = new System.Windows.Forms.TextBox();
			this.lamp1 = new System.Windows.Forms.PictureBox();
			this.lamp2 = new System.Windows.Forms.PictureBox();
			this.lamp3 = new System.Windows.Forms.PictureBox();
			this.lamp4 = new System.Windows.Forms.PictureBox();
			this.AlarmCb = new System.Windows.Forms.CheckBox();
			this.LampCb = new System.Windows.Forms.CheckBox();
			this.motionCb = new System.Windows.Forms.CheckBox();
			this.TemperatureCb = new System.Windows.Forms.CheckBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.clearLogBtn = new System.Windows.Forms.Button();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.newPass = new System.Windows.Forms.TextBox();
			this.buttonCb = new System.Windows.Forms.CheckBox();
			((System.ComponentModel.ISupportInitialize)(this.lamp1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp4)).BeginInit();
			this.SuspendLayout();
			// 
			// currentPass
			// 
			this.currentPass.Location = new System.Drawing.Point(269, 232);
			this.currentPass.Name = "currentPass";
			this.currentPass.Size = new System.Drawing.Size(468, 38);
			this.currentPass.TabIndex = 1;
			this.currentPass.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
			// 
			// changePass
			// 
			this.changePass.Location = new System.Drawing.Point(371, 428);
			this.changePass.Name = "changePass";
			this.changePass.Size = new System.Drawing.Size(267, 91);
			this.changePass.TabIndex = 2;
			this.changePass.Text = "Change password";
			this.changePass.UseVisualStyleBackColor = true;
			this.changePass.Click += new System.EventHandler(this.button1_Click);
			// 
			// datebtn
			// 
			this.datebtn.Location = new System.Drawing.Point(371, 865);
			this.datebtn.Name = "datebtn";
			this.datebtn.Size = new System.Drawing.Size(261, 101);
			this.datebtn.TabIndex = 3;
			this.datebtn.Text = "set date and time";
			this.datebtn.UseVisualStyleBackColor = true;
			this.datebtn.Click += new System.EventHandler(this.datebtn_Click);
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(269, 798);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(441, 38);
			this.textBox2.TabIndex = 4;
			this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
			// 
			// logBox
			// 
			this.logBox.BackColor = System.Drawing.SystemColors.Window;
			this.logBox.Location = new System.Drawing.Point(1117, 583);
			this.logBox.Multiline = true;
			this.logBox.Name = "logBox";
			this.logBox.ReadOnly = true;
			this.logBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.logBox.Size = new System.Drawing.Size(1331, 561);
			this.logBox.TabIndex = 5;
			// 
			// lamp1
			// 
			this.lamp1.Image = global::SmartHouse.Properties.Resources.lamp_off;
			this.lamp1.Location = new System.Drawing.Point(1015, 104);
			this.lamp1.Name = "lamp1";
			this.lamp1.Size = new System.Drawing.Size(360, 360);
			this.lamp1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.lamp1.TabIndex = 6;
			this.lamp1.TabStop = false;
			this.lamp1.Click += new System.EventHandler(this.lamp1_Click);
			// 
			// lamp2
			// 
			this.lamp2.Image = global::SmartHouse.Properties.Resources.lamp_off;
			this.lamp2.Location = new System.Drawing.Point(1406, 104);
			this.lamp2.Name = "lamp2";
			this.lamp2.Size = new System.Drawing.Size(360, 360);
			this.lamp2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.lamp2.TabIndex = 7;
			this.lamp2.TabStop = false;
			this.lamp2.Click += new System.EventHandler(this.lamp2_Click);
			// 
			// lamp3
			// 
			this.lamp3.Image = global::SmartHouse.Properties.Resources.lamp_off;
			this.lamp3.Location = new System.Drawing.Point(1799, 104);
			this.lamp3.Name = "lamp3";
			this.lamp3.Size = new System.Drawing.Size(360, 360);
			this.lamp3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.lamp3.TabIndex = 8;
			this.lamp3.TabStop = false;
			this.lamp3.Click += new System.EventHandler(this.lamp3_Click);
			// 
			// lamp4
			// 
			this.lamp4.Image = global::SmartHouse.Properties.Resources.lamp_off;
			this.lamp4.Location = new System.Drawing.Point(2194, 104);
			this.lamp4.Name = "lamp4";
			this.lamp4.Size = new System.Drawing.Size(360, 360);
			this.lamp4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.lamp4.TabIndex = 9;
			this.lamp4.TabStop = false;
			this.lamp4.Click += new System.EventHandler(this.lamp4_Click);
			// 
			// AlarmCb
			// 
			this.AlarmCb.AutoSize = true;
			this.AlarmCb.Checked = true;
			this.AlarmCb.CheckState = System.Windows.Forms.CheckState.Checked;
			this.AlarmCb.Location = new System.Drawing.Point(1225, 530);
			this.AlarmCb.Name = "AlarmCb";
			this.AlarmCb.Size = new System.Drawing.Size(127, 36);
			this.AlarmCb.TabIndex = 10;
			this.AlarmCb.Text = "Alarm";
			this.AlarmCb.UseVisualStyleBackColor = true;
			this.AlarmCb.CheckedChanged += new System.EventHandler(this.AlarmCb_CheckedChanged);
			// 
			// LampCb
			// 
			this.LampCb.AutoSize = true;
			this.LampCb.Checked = true;
			this.LampCb.CheckState = System.Windows.Forms.CheckState.Checked;
			this.LampCb.Location = new System.Drawing.Point(1427, 530);
			this.LampCb.Name = "LampCb";
			this.LampCb.Size = new System.Drawing.Size(138, 36);
			this.LampCb.TabIndex = 11;
			this.LampCb.Text = "Lamps";
			this.LampCb.UseVisualStyleBackColor = true;
			this.LampCb.CheckedChanged += new System.EventHandler(this.LampCb_CheckedChanged);
			// 
			// motionCb
			// 
			this.motionCb.AutoSize = true;
			this.motionCb.Checked = true;
			this.motionCb.CheckState = System.Windows.Forms.CheckState.Checked;
			this.motionCb.Location = new System.Drawing.Point(1613, 530);
			this.motionCb.Name = "motionCb";
			this.motionCb.Size = new System.Drawing.Size(153, 36);
			this.motionCb.TabIndex = 12;
			this.motionCb.Text = "Motions";
			this.motionCb.UseVisualStyleBackColor = true;
			this.motionCb.CheckedChanged += new System.EventHandler(this.motionCb_CheckedChanged);
			// 
			// TemperatureCb
			// 
			this.TemperatureCb.AutoSize = true;
			this.TemperatureCb.Checked = true;
			this.TemperatureCb.CheckState = System.Windows.Forms.CheckState.Checked;
			this.TemperatureCb.Location = new System.Drawing.Point(1799, 530);
			this.TemperatureCb.Name = "TemperatureCb";
			this.TemperatureCb.Size = new System.Drawing.Size(215, 36);
			this.TemperatureCb.TabIndex = 13;
			this.TemperatureCb.Text = "Temperature";
			this.TemperatureCb.UseVisualStyleBackColor = true;
			this.TemperatureCb.CheckedChanged += new System.EventHandler(this.TemperatureCb_CheckedChanged);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(1149, 45);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(113, 32);
			this.label1.TabIndex = 14;
			this.label1.Text = "Room 1";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(1539, 45);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(113, 32);
			this.label2.TabIndex = 15;
			this.label2.Text = "Room 2";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(1935, 45);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(113, 32);
			this.label3.TabIndex = 16;
			this.label3.Text = "Room 3";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(2330, 45);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(113, 32);
			this.label4.TabIndex = 17;
			this.label4.Text = "Room 4";
			// 
			// clearLogBtn
			// 
			this.clearLogBtn.Location = new System.Drawing.Point(2283, 517);
			this.clearLogBtn.Name = "clearLogBtn";
			this.clearLogBtn.Size = new System.Drawing.Size(145, 60);
			this.clearLogBtn.TabIndex = 18;
			this.clearLogBtn.Text = "Clear";
			this.clearLogBtn.UseVisualStyleBackColor = true;
			this.clearLogBtn.Click += new System.EventHandler(this.clearLogBtn_Click);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(32, 232);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(231, 32);
			this.label5.TabIndex = 19;
			this.label5.Text = "current password";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(68, 337);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(195, 32);
			this.label6.TabIndex = 21;
			this.label6.Text = "new password";
			// 
			// newPass
			// 
			this.newPass.Location = new System.Drawing.Point(269, 337);
			this.newPass.Name = "newPass";
			this.newPass.Size = new System.Drawing.Size(468, 38);
			this.newPass.TabIndex = 20;
			// 
			// buttonCb
			// 
			this.buttonCb.AutoSize = true;
			this.buttonCb.Checked = true;
			this.buttonCb.CheckState = System.Windows.Forms.CheckState.Checked;
			this.buttonCb.Location = new System.Drawing.Point(2053, 530);
			this.buttonCb.Name = "buttonCb";
			this.buttonCb.Size = new System.Drawing.Size(150, 36);
			this.buttonCb.TabIndex = 22;
			this.buttonCb.Text = "Buttons";
			this.buttonCb.UseVisualStyleBackColor = true;
			this.buttonCb.CheckedChanged += new System.EventHandler(this.buttonCb_CheckedChanged);
			// 
			// Form1
			// 
			this.AcceptButton = this.changePass;
			this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 31F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(2594, 1449);
			this.Controls.Add(this.buttonCb);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.newPass);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.clearLogBtn);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.TemperatureCb);
			this.Controls.Add(this.motionCb);
			this.Controls.Add(this.LampCb);
			this.Controls.Add(this.AlarmCb);
			this.Controls.Add(this.lamp4);
			this.Controls.Add(this.lamp3);
			this.Controls.Add(this.lamp2);
			this.Controls.Add(this.lamp1);
			this.Controls.Add(this.logBox);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.datebtn);
			this.Controls.Add(this.changePass);
			this.Controls.Add(this.currentPass);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			((System.ComponentModel.ISupportInitialize)(this.lamp1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.lamp4)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.TextBox currentPass;
		private System.Windows.Forms.Button changePass;
		private System.Windows.Forms.Button datebtn;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox logBox;
		private System.Windows.Forms.PictureBox lamp1;
		private System.Windows.Forms.PictureBox lamp2;
		private System.Windows.Forms.PictureBox lamp3;
		private System.Windows.Forms.PictureBox lamp4;
		private System.Windows.Forms.CheckBox AlarmCb;
		private System.Windows.Forms.CheckBox LampCb;
		private System.Windows.Forms.CheckBox motionCb;
		private System.Windows.Forms.CheckBox TemperatureCb;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button clearLogBtn;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox newPass;
		private System.Windows.Forms.CheckBox buttonCb;
	}
}

