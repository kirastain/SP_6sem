using System;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace FDALab3
{
    public partial class Form1 : Form
    {
        bool ChildProcess = false;

        [DllImport("ThreadLibrary.dll")] private static extern void Init();
        [DllImport("ThreadLibrary.dll")] private static extern int sendInt(int n);
        [DllImport("ThreadLibrary.dll")] private static extern int confirm();
        [DllImport("ThreadLibrary.dll")] private static extern void sendString(string s);
        [DllImport("ThreadLibrary.dll")] private static extern void connectToServer();
        [DllImport("ThreadLibrary.dll")] private static extern void disconnect();
        public Form1()
        {
            InitializeComponent();
            ChildProcess = true;
            Init();
        }
        public Boolean mainThreadExist()
        {
            if (!ChildProcess)
            {
                threadListListBox.Items.Clear();
                return false;
            }
            return true;
        }
        private void startButton_Click(object sender, EventArgs e)
        {
            connectToServer();
            sendInt(0);
            int threadCount = confirm();
            disconnect();
            threadListListBox.Items.Clear();
            for (int j = 0; j < threadCount; j++)
            {
                threadListListBox.Items.Add("Thread " + j);
            }
        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            if (threadListListBox.Items.Count == 1)
                return;
            connectToServer();
            sendInt(1);

            int threadCount = confirm();
            disconnect();
            threadListListBox.Items.Clear();
            for (int j = 0; j < threadCount; j++)
            {
                threadListListBox.Items.Add("Thread " + j);
            }
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
        }

        private void messageButton_Click(object sender, EventArgs e)
        {
            connectToServer();
            sendInt(3);
            string message = MessageTextBox.Text;
            sendString(message);
            
            int threadCount = confirm();
            disconnect();
            threadListListBox.Items.Clear();
            for (int j = 0; j < threadCount; j++)
            {
                threadListListBox.Items.Add("Thread " + j);
            }
        }
    }
}
