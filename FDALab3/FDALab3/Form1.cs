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
        [DllImport("ThreadLibrary.dll")] private static extern bool programConfirm();
        [DllImport("ThreadLibrary.dll")] private static extern bool programWaitResponse();
        [DllImport("ThreadLibrary.dll")] private static extern bool Send(StringBuilder str, int eventNumber, int ThreadNumber = -1);
        [DllImport("ThreadLibrary.dll")] private static extern bool Init();
        public Form1()
        {
            InitializeComponent();
        }
        public Boolean mainThreadExists()
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
            for (int i = 0; i < Int32.Parse(threadNumberTextBox.Text); ++i)
            {
                if (mainThreadExists())
                {
                    Send(new StringBuilder(""), 0);
                    programWaitResponse();

                    threadListListBox.Items.Add("Thread" + threadListListBox.Items.Count.ToString());
                }
                else
                {
                    ChildProcess = true;
                    Init();
                    threadListListBox.Items.Add("Main thread");
                    break;
                }
            }
        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            if (!mainThreadExists())
                return;

            Send(new StringBuilder(""), 1);
            programWaitResponse();

            threadListListBox.Items.RemoveAt(threadListListBox.Items.Count - 1);
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!mainThreadExists())
                return;

            Send(new StringBuilder(""), 2);
            programWaitResponse();
        }

        private void messageButton_Click(object sender, EventArgs e)
        {
            string message = MessageTextBox.Text;
            Send(new StringBuilder(message), 3);
            programWaitResponse();
        }

        private void threadListListBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
