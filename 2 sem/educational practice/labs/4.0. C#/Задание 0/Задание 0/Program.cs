using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Collections.Generic;
using System.Web.UI;

namespace Задание_0
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.Run(new AppWindow("Задача 0", 850, 650));
        }
    }

    class AppWindow : Form
    {
        private void AppWindow_FormClosing(Object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("Уверены, что не пожалеете?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                e.Cancel = true;
        }
        private void AppWindow_Resize(object sender, System.EventArgs e)
        {
            ArrangeClientArea();
        }
        public AppWindow(string tittle, int width, int height)
        {
            FormClosing += AppWindow_FormClosing;
            Resize += AppWindow_Resize;
            Text = tittle;
            if (width > 0)
                Width = width;
            if (height > 0)
                Height = height;
            CenterToScreen();
            BuildControls();
        }
        private void BuildControls()
        {
            BuildToolTip();
            BuildMenu();
            BuildStatusLine();
            BuildButton();
            ArrangeClientArea();
            MinimumSize = AppMinSize(NcSize.Width = (Width - ClientSize.Width + 1), NcSize.Height = (Width - ClientSize.Height + 1));
        }
        private Size NcSize = new Size();
        private Rectangle GetClientRectangle()
        {
            return new Rectangle(NcSize.Width / 2, mnuMain.Bounds.Bottom, Width - NcSize.Width, statusStrip.Bounds.Top - mnuMain.Bounds.Bottom);
        }
        private Size AppMinSize(int ncWidth, int ncHeight)
        {
            ncWidth += btnClickMe.Width;
            ncHeight += btnClickMe.Height;
            ncHeight += mnuMain.Height + statusStrip.Height;
            return new Size(ncWidth, ncHeight);
        }
        private void ArrangeClientArea()
        {
            if (btnClickMe != null)
                btnClickMe.SetBounds((ClientSize.Width - btnClickMe.Width) / 2 + 1, (ClientSize.Height - btnClickMe.Height * 2) + 1, btnClickMe.Width, btnClickMe.Height);
            if (ChartName != "")
                MainChart.SetBounds(0, 0, ClientSize.Width, ClientSize.Height * 3 / 4);
        }
        private StatusStrip statusStrip;
        private ToolStripStatusLabel toolStripStatusLabel;
        private void BuildStatusLine()
        {
            statusStrip = new StatusStrip();
            toolStripStatusLabel = new ToolStripStatusLabel();

            statusStrip.SuspendLayout();
            SuspendLayout();

            statusStrip.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel });
            statusStrip.Location = new Point(0, 248);
            statusStrip.Name = "statusStrip";
            statusStrip.Size = new Size(292, 30);
            statusStrip.TabIndex = 0;
            statusStrip.Text = "statusStrip";

            toolStripStatusLabel.BorderSides = 0;
            toolStripStatusLabel.BorderStyle = Border3DStyle.Flat;
            toolStripStatusLabel.IsLink = false;
            toolStripStatusLabel.Name = "toolStripStatusLabel";
            toolStripStatusLabel.Size = new Size(246, 28);
            toolStripStatusLabel.Spring = true;
            toolStripStatusLabel.Text = "";
            toolStripStatusLabel.Alignment = ToolStripItemAlignment.Left;
            toolStripStatusLabel.TextAlign = ContentAlignment.TopLeft;

            Controls.Add(statusStrip);

            statusStrip.ResumeLayout(false);
            statusStrip.PerformLayout();

            ResumeLayout(false);
            PerformLayout();
        }
        private MenuStrip mnuMain = new MenuStrip();
        private ToolStripMenuItem mnuFile = new ToolStripMenuItem();
        private ToolStripMenuItem mnuFileChFolder = new ToolStripMenuItem();
        private ToolStripMenuItem mnuFileOpenFile = new ToolStripMenuItem();

        private ToolStripMenuItem mnuFileSaveAsFile = new ToolStripMenuItem();
        private ToolStripMenuItem mnuFileExit = new ToolStripMenuItem();
        private ToolStripMenuItem mnuHelp = new ToolStripMenuItem();
        private ToolStripMenuItem mnuHelpAbout = new ToolStripMenuItem();

        private void BuildMenu()
        {
            mnuFile.Text = "&Файл";
            mnuMain.Items.Add(mnuFile);
            mnuHelp.Text = "&Помощь";
            mnuMain.Items.Add(mnuHelp);

            mnuFileOpenFile.Text = "&Открыть";
            mnuFile.DropDownItems.Add(mnuFileOpenFile);
            mnuFileOpenFile.Click += (o, s) => OnFileOpen();
            mnuFileOpenFile.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Открываем файл";
            mnuFileOpenFile.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            mnuFile.DropDownItems.Add(new ToolStripSeparator());

            mnuFileExit.Text = "&Выход";
            mnuFile.DropDownItems.Add(mnuFileExit);
            mnuFileExit.Click += (o, s) => Application.Exit();
            mnuFileExit.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Выход из программы";
            mnuFileExit.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            mnuHelpAbout.Text = "&О программе";
            mnuHelp.DropDownItems.Add(mnuHelpAbout);
            mnuHelpAbout.Click += (o, s) => OnHelpAbout();
            mnuHelpAbout.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Лучше не надо";
            mnuHelpAbout.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            Controls.Add(mnuMain);
            MainMenuStrip = mnuMain;
        }

        private Button btnClickMe = new Button();
        private void BuildButton()
        {
            btnClickMe.Text = "Да появится диаграмма!";
            btnClickMe.SetBounds(50, 50, 100, 50);
            btnClickMe.Click += (o, s) => onButtonClicked();
            btnClickMe.MouseEnter += (o, s) => toolStripStatusLabel.Text = "*Тык*";
            btnClickMe.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";
            toolTip.SetToolTip(btnClickMe as Control, "Click");
            Controls.Add(btnClickMe);
        }
        ToolTip toolTip = new ToolTip();

        private void onButtonClicked()
        {
            if (ChartName == "")
            {
                MessageBox.Show("Выберите файл");
                return;
            }
            BuildChart(ChartName);
            MainChart.Series["Opros"].Points.Clear();
            for (int i = 0; i < DataList.Count; i++)
                MainChart.Series["Opros"].Points.AddXY(DataList[i].GetElName(), DataList[i].GetElCount());
            Random rand = new Random();
            switch (rand.Next(0, 7))
            {
                case 0: btnClickMe.BackColor = Color.DarkRed; break;
                case 1: btnClickMe.BackColor = Color.DarkGreen; break;
                case 2: btnClickMe.BackColor = Color.DarkBlue; break;
                case 3: btnClickMe.BackColor = Color.DarkSeaGreen; break;
                case 4: btnClickMe.BackColor = Color.WhiteSmoke; break;
                case 5: btnClickMe.BackColor = Color.DarkSalmon; break;
                case 6: btnClickMe.BackColor = Color.DarkOliveGreen; break;
            }
        }

        private void BuildToolTip()
        {
            toolTip.AutoPopDelay = 5000;
            toolTip.InitialDelay = 1000;
            toolTip.ReshowDelay = 500;
            toolTip.ShowAlways = true;
        }
        private struct DataElement
        {
            String ElName; int ElCount;
            public DataElement(String n, int c) { ElName = n; ElCount = c; }
            public String GetElName() { return ElName; }
            public int GetElCount() { return ElCount; }
        }
        List<DataElement> DataList = new List<DataElement>();
        String ChartName = "";
        private void OnFileOpen()
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                openFileDialog.Filter = "Text files (*.txt) |*.txt|All files (*.*) |*.*";
                openFileDialog.FilterIndex = 0;
                openFileDialog.DefaultExt = "txt";
                openFileDialog.FileName = "*.txt*";

                openFileDialog.RestoreDirectory = true;
                openFileDialog.Multiselect = false;

                openFileDialog.ShowDialog();
                String sString;
                StreamReader sreader = new StreamReader(openFileDialog.FileName, System.Text.Encoding.GetEncoding(1251));
                ChartName = sreader.ReadLine();
                while ((sString = sreader.ReadLine()) != null)
                {
                    int x = sString.IndexOf(' ');
                    DataElement Car = new DataElement(sString.Substring(x + 1), Convert.ToInt32(sString.Substring(0, x)));
                    DataList.Add(Car);
                }
                sreader.Close();
            }
        }
        private void BuildChart(String title)
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.MainChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            ((System.ComponentModel.ISupportInitialize)(this.MainChart)).BeginInit();
            this.MainChart.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.MainChart.ForeColor = Color.White;
            this.MainChart.BackColor = Color.Black;
            chartArea1.BackColor = Color.Black;
            series1.Color= Color.Black;
            legend1.ForeColor= Color.White;
            legend1.BackColor = Color.Black;
            chartArea1.Name = "ChartArea1";
            this.MainChart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.MainChart.Legends.Add(legend1);
            this.MainChart.Location = new System.Drawing.Point(0, 20);
            this.MainChart.Name = "MainChart";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Pie;
            series1.Legend = "Legend1";
            series1.Name = "Opros";
            series1.YValuesPerPoint = 2;
            this.MainChart.Series.Add(series1);
            this.MainChart.Size = new System.Drawing.Size(ClientSize.Width, ClientSize.Height * 8 / 10);
            this.MainChart.TabIndex = 0;
            this.MainChart.Text = "Chart";
            title1.Name = "title1";
            title1.Text = title;
            title1.ForeColor = Color.White;
            this.MainChart.Titles.Add(title1);
            this.Controls.Add(this.MainChart);
            this.Name = "AppWindow";
            ((System.ComponentModel.ISupportInitialize)(this.MainChart)).EndInit();
            this.ResumeLayout(false);
        }

        private System.Windows.Forms.DataVisualization.Charting.Chart MainChart;

        private void OnHelpAbout()
        {
            MessageBox.Show("Задача с диаграммой\nАлина Крагель, 1 курс, 10 группа, 27.03.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}

