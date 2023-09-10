using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Задание_5
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                Form1 FF = new Form1();
                string String = "";
                String += textBox1.Text + "|" + textBox2.Text;
                FF.AddLInf(String);
                this.Close();
            }
            else 
                MessageBox.Show("Значения полей пусты.", "Внимательнее", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
