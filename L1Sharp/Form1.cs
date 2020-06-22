using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;

namespace L1Sharp
{
    public partial class Form1 : Form //генерация формы на шарпе
    {
        Process ChildProcess = null;
        //EventWaitHandle - класс, позволяющий взаимодействие между потоками
        EventWaitHandle eventStop = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStop");
        EventWaitHandle eventStart = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStart");
        EventWaitHandle eventConfirm = new EventWaitHandle(false, EventResetMode.ManualReset, "eventConfirm");
        EventWaitHandle eventQuit = new EventWaitHandle(false, EventResetMode.AutoReset, "eventQuit");
        int k;

        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e) //1 - , 2 - 
        {
            if (ChildProcess == null || ChildProcess.HasExited) //говорит об отсутствии процесса или завершении
            {
                ChildProcess = Process.Start("L1\\L1.exe"); //запустить процесс с++, консоль
                ThreadList.Items.Clear(); //очистка списка
                ThreadList.Items.Add("All threads");
                ThreadList.Items.Add("Main thread");
                threadCountField.Enabled = true; //счетчик над кнопками
                k = 0;
            }
            else
            {
                for (var i = 0; i < threadCountField.Value; i++) //по заданному количестве на шкале
                {
                    eventStart.Set(); //метод, уведомляющий, что событие произошло
                    eventConfirm.WaitOne(); //ручное, ждет сигнальное событие
                    ThreadList.Items.Add(String.Format("Thread {0}", k++)); //добавление процесса, счетчик
                    eventConfirm.Reset(); //несигнальное, блокирование потоков
                }
            }

        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            if (ChildProcess == null || ChildProcess.HasExited)
            {
                //если нет процессов и консоли, то ничего не происходит на кнопку
            }
            else
            {
                if (k == 0)
                {
                    
                    eventQuit.Set(); //сигнал
                    eventConfirm.WaitOne(); //ожидание сигнала
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1); //убирает два дефолтных процесса
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    threadCountField.Enabled = false; //выключает шкалу над кнопками
                }
                if (ThreadList.Items.Count != 0) { //если есть потоки в списке
                    eventStop.Set(); //остановить, сигнальное событие
                    eventConfirm.WaitOne(); //ожидает
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1); //убрать из списка
                    k--; //счетчик --
                    eventConfirm.Reset(); //блокирование
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e) //закрытие формы
        {
            if (ChildProcess != null && !ChildProcess.HasExited) //если не завершены процессы
            {
                ChildProcess.CloseMainWindow(); //закончить
                ChildProcess.Close();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
