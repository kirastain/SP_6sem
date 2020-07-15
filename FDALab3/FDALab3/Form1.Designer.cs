namespace FDALab3
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.startButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.messageButton = new System.Windows.Forms.Button();
            this.threadListListBox = new System.Windows.Forms.ListBox();
            this.threadNumberTextBox = new System.Windows.Forms.TextBox();
            this.MessageTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // startButton
            // 
            this.startButton.Location = new System.Drawing.Point(180, 87);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(121, 32);
            this.startButton.TabIndex = 0;
            this.startButton.Text = "Start";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(314, 87);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(121, 32);
            this.stopButton.TabIndex = 1;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // messageButton
            // 
            this.messageButton.Location = new System.Drawing.Point(180, 228);
            this.messageButton.Name = "messageButton";
            this.messageButton.Size = new System.Drawing.Size(255, 29);
            this.messageButton.TabIndex = 2;
            this.messageButton.Text = "Message";
            this.messageButton.UseVisualStyleBackColor = true;
            this.messageButton.Click += new System.EventHandler(this.messageButton_Click);
            // 
            // threadListListBox
            // 
            this.threadListListBox.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.threadListListBox.FormattingEnabled = true;
            this.threadListListBox.ItemHeight = 20;
            this.threadListListBox.Items.AddRange(new object[] {
            "Now it\'s empty:("});
            this.threadListListBox.Location = new System.Drawing.Point(516, 42);
            this.threadListListBox.Name = "threadListListBox";
            this.threadListListBox.Size = new System.Drawing.Size(240, 284);
            this.threadListListBox.TabIndex = 3;
            this.threadListListBox.SelectedIndexChanged += new System.EventHandler(this.threadListListBox_SelectedIndexChanged);
            // 
            // threadNumberTextBox
            // 
            this.threadNumberTextBox.Location = new System.Drawing.Point(180, 42);
            this.threadNumberTextBox.Name = "threadNumberTextBox";
            this.threadNumberTextBox.Size = new System.Drawing.Size(255, 26);
            this.threadNumberTextBox.TabIndex = 4;
            this.threadNumberTextBox.Text = "1";
            // 
            // MessageTextBox
            // 
            this.MessageTextBox.Location = new System.Drawing.Point(180, 186);
            this.MessageTextBox.Name = "MessageTextBox";
            this.MessageTextBox.Size = new System.Drawing.Size(255, 26);
            this.MessageTextBox.TabIndex = 5;
            this.MessageTextBox.Text = "Message";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Desktop;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.MessageTextBox);
            this.Controls.Add(this.threadNumberTextBox);
            this.Controls.Add(this.threadListListBox);
            this.Controls.Add(this.messageButton);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.startButton);
            this.Name = "Form1";
            this.Text = "FDA lab3";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Button messageButton;
        private System.Windows.Forms.ListBox threadListListBox;
        private System.Windows.Forms.TextBox threadNumberTextBox;
        private System.Windows.Forms.TextBox MessageTextBox;
    }
}

