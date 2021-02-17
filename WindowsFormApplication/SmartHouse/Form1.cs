using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace SmartHouse
{
	public partial class Form1 : Form
	{
		SerialPort mySerialPort;

		List<String> logs = new List<string>();
		List<String> filteredLogs = new List<string>();
		String logsString = "";

		bool alarmFilter = true, lampFilter = true, motionFilter = true, tempFilter = true, buttonFilter=true;
		public Form1()
		{
			InitializeComponent();

			this.FormClosing += Form1_FormClosing;

			mySerialPort = new SerialPort("COM6");
			mySerialPort.BaudRate = 38400;
			mySerialPort.Parity = Parity.None;
			mySerialPort.StopBits = StopBits.One;
			mySerialPort.DataBits = 8;
			mySerialPort.Handshake = Handshake.None;

			mySerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

			mySerialPort.Open();

			textBox2.Text = DateTime.Now.ToString("dd/MM/yyyy HH:mm");

			this.Location = new Point(0, 0);

			this.Size = new Size((int)((float)Screen.PrimaryScreen.WorkingArea.Size.Width * 0.7f), (int)((float)Screen.PrimaryScreen.WorkingArea.Size.Height* 0.7f));

		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
			mySerialPort.Close();
		}

		private void showLogs()
		{
			filteredLogs = new List<string>();
			for(int i = logs.Count() - 1; i>=0; i--)
			{
				if (
					(!alarmFilter && logs[i].Contains("Alarm")) ||
					(!lampFilter && logs[i].Contains("Lamp")) ||
					(!motionFilter && logs[i].Contains("Move")) ||
					(!buttonFilter && logs[i].Contains("button")) ||
					(!tempFilter && logs[i].Contains("temp"))
					)
					continue;
				else
				{
					filteredLogs.Add(logs[i]);
				}

			}
			logBox.BeginInvoke((MethodInvoker)delegate () {
				//logBox.AppendText(indata+ "\r\n");
				logBox.Text = string.Join("\n", filteredLogs.ToArray());
				//logBox.Text = logsString;
				//logBox.AppendText(" ");
			});
		}

		private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
		{
			SerialPort sp = (SerialPort)sender;
			string indata = sp.ReadExisting();

			logsString += indata;
			logs = logsString.Split('\n').ToList();

			showLogs();


			String lastLog = logs[logs.Count-2];
			if (lastLog.EndsWith("\r"))
			{
				Debug.WriteLine(lastLog);

				string logBody = lastLog.Substring(20);

				if (logBody.StartsWith("Room") && logBody.Contains("Lamp"))
				{
					int roomNumber = logBody[5] - '0';
					PictureBox lamp;
					if (roomNumber == 1) lamp = lamp1;
					else if (roomNumber == 2) lamp = lamp2;
					else if (roomNumber == 3) lamp = lamp3;
					else lamp = lamp4;
					char tmp = logBody[logBody.Count() - 2];
					if (logBody[logBody.Count() - 2] == 'n')
					{
						lamp.Image = Properties.Resources.lamp_on;
					}
					else
					{
						lamp.Image = Properties.Resources.lamp_off;
					}
				}
			}
			
		}
		private void Form1_Load(object sender, EventArgs e)
		{

		}

		private void textBox1_TextChanged(object sender, EventArgs e)
		{

		}

		private void label1_Click(object sender, EventArgs e)
		{
	
		}

		private void button1_Click(object sender, EventArgs e)
		{
			mySerialPort.WriteLine("Change Password "+ currentPass.Text + " " + newPass.Text);
		}

		private void datebtn_Click(object sender, EventArgs e)
		{
			if(textBox2.Text == "")
				mySerialPort.WriteLine("SetDateTime " + DateTime.Now.ToString("dd/MM/yyyy HH:mm"));
			else
				mySerialPort.WriteLine("SetDateTime " + textBox2.Text);
		}

		private void textBox2_TextChanged(object sender, EventArgs e)
		{

		}

		private void pictureBox4_Click(object sender, EventArgs e)
		{

		}

		private void AlarmCb_CheckedChanged(object sender, EventArgs e)
		{
			alarmFilter = AlarmCb.Checked;
			showLogs();
		}

		private void clearLogBtn_Click(object sender, EventArgs e)
		{
			logsString = "";
			showLogs();
		}

		private void lamp1_Click(object sender, EventArgs e)
		{
			mySerialPort.WriteLine("Lamp Room 0");
		}

		private void lamp2_Click(object sender, EventArgs e)
		{
			mySerialPort.WriteLine("Lamp Room 1");
		}

		private void lamp3_Click(object sender, EventArgs e)
		{
			mySerialPort.WriteLine("Lamp Room 2");
		}

		private void lamp4_Click(object sender, EventArgs e)
		{
			mySerialPort.WriteLine("Lamp Room 3");
		}

		private void buttonCb_CheckedChanged(object sender, EventArgs e)
		{
			buttonFilter = buttonCb.Checked;
			showLogs();
		}

		private void LampCb_CheckedChanged(object sender, EventArgs e)
		{
			lampFilter = LampCb.Checked;
			showLogs();

		}

		private void motionCb_CheckedChanged(object sender, EventArgs e)
		{
			motionFilter = motionCb.Checked;
			showLogs();

		}

		private void TemperatureCb_CheckedChanged(object sender, EventArgs e)
		{
			tempFilter = TemperatureCb.Checked;
			showLogs();

		}
	}
}

