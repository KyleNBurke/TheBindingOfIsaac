namespace MapConverter
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
            this.label1 = new System.Windows.Forms.Label();
            this.fileDirTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.outputDirTextBox = new System.Windows.Forms.TextBox();
            this.fileDirButton = new System.Windows.Forms.Button();
            this.outputDirButton = new System.Windows.Forms.Button();
            this.convertButton = new System.Windows.Forms.Button();
            this.exitButton = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.panel = new System.Windows.Forms.Panel();
            this.panel.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "File Directory";
            // 
            // fileDirTextBox
            // 
            this.fileDirTextBox.Location = new System.Drawing.Point(12, 37);
            this.fileDirTextBox.Name = "fileDirTextBox";
            this.fileDirTextBox.Size = new System.Drawing.Size(580, 26);
            this.fileDirTextBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 71);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(125, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Output Directory";
            // 
            // outputDirTextBox
            // 
            this.outputDirTextBox.Location = new System.Drawing.Point(12, 94);
            this.outputDirTextBox.Name = "outputDirTextBox";
            this.outputDirTextBox.Size = new System.Drawing.Size(580, 26);
            this.outputDirTextBox.TabIndex = 3;
            // 
            // fileDirButton
            // 
            this.fileDirButton.AutoSize = true;
            this.fileDirButton.Location = new System.Drawing.Point(603, 35);
            this.fileDirButton.Name = "fileDirButton";
            this.fileDirButton.Size = new System.Drawing.Size(63, 30);
            this.fileDirButton.TabIndex = 4;
            this.fileDirButton.Text = "...";
            this.fileDirButton.UseVisualStyleBackColor = true;
            this.fileDirButton.Click += new System.EventHandler(this.fileDirButton_Click);
            // 
            // outputDirButton
            // 
            this.outputDirButton.AutoSize = true;
            this.outputDirButton.Location = new System.Drawing.Point(603, 92);
            this.outputDirButton.Name = "outputDirButton";
            this.outputDirButton.Size = new System.Drawing.Size(63, 30);
            this.outputDirButton.TabIndex = 5;
            this.outputDirButton.Text = "...";
            this.outputDirButton.UseVisualStyleBackColor = true;
            this.outputDirButton.Click += new System.EventHandler(this.outputDirButton_Click);
            // 
            // convertButton
            // 
            this.convertButton.AutoSize = true;
            this.convertButton.Location = new System.Drawing.Point(562, 151);
            this.convertButton.Name = "convertButton";
            this.convertButton.Size = new System.Drawing.Size(104, 31);
            this.convertButton.TabIndex = 6;
            this.convertButton.Text = "Convert";
            this.convertButton.UseVisualStyleBackColor = true;
            this.convertButton.Click += new System.EventHandler(this.convertButton_Click);
            // 
            // exitButton
            // 
            this.exitButton.AutoSize = true;
            this.exitButton.Location = new System.Drawing.Point(452, 151);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(104, 31);
            this.exitButton.TabIndex = 7;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "tmx";
            this.openFileDialog.Filter = "Tiled map file (*.tmx)|*.tmx";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.DefaultExt = "bim";
            this.saveFileDialog.Filter = "The Binding of Isaac map file (*.bim)|*.bim";
            // 
            // panel
            // 
            this.panel.Controls.Add(this.exitButton);
            this.panel.Controls.Add(this.label1);
            this.panel.Controls.Add(this.convertButton);
            this.panel.Controls.Add(this.fileDirTextBox);
            this.panel.Controls.Add(this.outputDirButton);
            this.panel.Controls.Add(this.label2);
            this.panel.Controls.Add(this.fileDirButton);
            this.panel.Controls.Add(this.outputDirTextBox);
            this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel.Location = new System.Drawing.Point(0, 0);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(678, 194);
            this.panel.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(678, 194);
            this.Controls.Add(this.panel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "The Binding of Isaac Map Convert";
            this.panel.ResumeLayout(false);
            this.panel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox fileDirTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox outputDirTextBox;
        private System.Windows.Forms.Button fileDirButton;
        private System.Windows.Forms.Button outputDirButton;
        private System.Windows.Forms.Button convertButton;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.Panel panel;
    }
}

