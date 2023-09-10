using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Задание_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
           
        }

        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {
           
        }

        private void radioButton8_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
           
        }

        OpenFileDialog openFileDialog = new OpenFileDialog();

        private void inputFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Text files (*.txt) |*.txt|All files (*.*) |*.*";
            openFileDialog.FilterIndex = 0;
            openFileDialog.DefaultExt = "txt";
            openFileDialog.FileName = "*.txt*";

            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            openFileDialog.ShowDialog();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача 1\nАлина Крагель, 1 курс, 10 группа, 03.04.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
           
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog.FileName == "")
                if (openFileDialog.ShowDialog() != DialogResult.OK)
                    return;
            if (radioButton1.Checked == false && radioButton2.Checked == false && radioButton3.Checked == false && radioButton4.Checked == false)
            {
                MessageBox.Show("Выберите входную кодировку", "Внимательно!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            if (radioButton5.Checked == false && radioButton6.Checked == false && radioButton7.Checked == false && radioButton8.Checked == false)
            {
                MessageBox.Show("Выберите выходную кодировку", "Внимательно!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            if (radioButton1.Checked==true)
            {
                Encoding IEncoding = Encoding.GetEncoding("koi8-r");
                if (radioButton8.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("koi8-r");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton7.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding(1251);
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton6.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("utf-8");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton5.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("cp866");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
            }
            if (radioButton2.Checked == true)
            {
                Encoding IEncoding = Encoding.GetEncoding(1251);
                if (radioButton8.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("koi8-r");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton7.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding(1251);
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton6.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("utf-8");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton5.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("cp866");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
            }
            if (radioButton3.Checked == true)
            {
                Encoding IEncoding = Encoding.GetEncoding("utf-8");
                if (radioButton8.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("koi8-r");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton7.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding(1251);
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton6.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("utf-8");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton5.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("cp866");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
            }
            if (radioButton4.Checked == true)
            {
                Encoding IEncoding = Encoding.GetEncoding("cp866");
                if (radioButton8.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("koi8-r");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton7.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding(1251);
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton6.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("utf-8");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
                if (radioButton5.Checked == true)
                {
                    Encoding OEncoding = Encoding.GetEncoding("cp866");
                    File.WriteAllText(openFileDialog.FileName, File.ReadAllText(openFileDialog.FileName, IEncoding), OEncoding);
                }
            }
            MessageBox.Show("Файл перекодирован", "Сообщение о завершении", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
