using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Задание_4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        OpenFileDialog openFileDialog = new OpenFileDialog();
        FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        private void chooseImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Image files (*.BMP, *.JPG, *.PNG, *.GIF) |*.BMP; *.JPG; *.PNG; *.GIF|All files (*.*) |*.*";
            openFileDialog.FilterIndex = 0;
            //openFileDialog.DefaultExt = "GIF";
            //openFileDialog.FileName = "*.GIF*";

            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    pictureBox1.Image = new Bitmap(openFileDialog.FileName);
                }
                catch
                {
                    MessageBox.Show("Ошибка открытия вбыранного файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            };
        }

        private void chooseFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog())
            {
                folderBrowserDialog.ShowNewFolderButton = false;
                folderBrowserDialog.SelectedPath = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
                if (folderBrowserDialog.ShowDialog(this) == DialogResult.OK)
                    MessageBox.Show("Выбранная для сохранения папка: " + folderBrowserDialog.SelectedPath);
                saveFileDialog.InitialDirectory = folderBrowserDialog.SelectedPath;
                System.IO.Directory.SetCurrentDirectory(folderBrowserDialog.SelectedPath);
                saveFileDialog.DefaultExt = "gif";
                saveFileDialog.FileName = "peace ";
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача 4\nАлина Крагель, 1 курс, 10 группа, 10.04.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button1_Click(object sender, EventArgs e)
        {
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        pictureBox1.Image = new Bitmap(openFileDialog.FileName);
                    }
                    catch
                    {
                        MessageBox.Show("Ошибка открытия вбыранного файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }

        }

        bool IsDigitsOnly(string str)
        {
            foreach (char c in str)
                if (c < '0' || c > '9')
                    return false;
            return true;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
 
        }
        int l = 1;
        private void button2_Click(object sender, EventArgs e)
        {
            int V = 0, H = 0;
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                if (IsDigitsOnly(textBox1.Text))
                    V = int.Parse(textBox1.Text);
                else
                    MessageBox.Show("Поле \"Вертикаль\" содержит неверный символ.\nДолжно быть целое количество частей.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                if (IsDigitsOnly(textBox2.Text))
                    H = int.Parse(textBox2.Text);
                else
                    MessageBox.Show("Поле \"Горизонталь\" содержит неверный символ.\nДолжно быть целое количество частей.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
                MessageBox.Show("Значения(-е) полей(-я) пусты(-о).\nДолжно быть целое количество частей.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            if(V==0||H==0||(V==0&&H==0))
                MessageBox.Show("Значения(-е) полей(-я) являют-(ят)ся 0.\nДолжно быть целое количество частей.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);


            if (openFileDialog.FileName == "")
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        pictureBox1.Image = new Bitmap(openFileDialog.FileName);
                    }
                    catch
                    {
                        MessageBox.Show("Ошибка открытия вбыранного файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }

            if (saveFileDialog.FileName == "")
                {
                    folderBrowserDialog.ShowNewFolderButton = false;
                    folderBrowserDialog.SelectedPath = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                    folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
                    if (folderBrowserDialog.ShowDialog(this) == DialogResult.OK)
                        MessageBox.Show("Выбранная для сохранения папка: " + folderBrowserDialog.SelectedPath);
                    saveFileDialog.InitialDirectory = folderBrowserDialog.SelectedPath;
                    System.IO.Directory.SetCurrentDirectory(folderBrowserDialog.SelectedPath);
                    saveFileDialog.DefaultExt = "gif";
                    saveFileDialog.FileName = "peace ";
                }
            for (int i=0; i< H; i++)
                for (int j = 0; j < V; j++)
                {
                    Rectangle RC;
                    if (i * pictureBox1.Image.Width / H + pictureBox1.Image.Width / H > pictureBox1.Image.Width && j * pictureBox1.Image.Height / V + pictureBox1.Image.Height / V < pictureBox1.Image.Height)
                        RC = new Rectangle(new Point(i * pictureBox1.Image.Width / H, j * pictureBox1.Image.Height / V), new Size(pictureBox1.Image.Width - i * pictureBox1.Image.Width / H, pictureBox1.Image.Height / V));
                    else
                        if (i * pictureBox1.Image.Width / H + pictureBox1.Image.Width / H < pictureBox1.Image.Width && j * pictureBox1.Image.Height / V + pictureBox1.Image.Height / V > pictureBox1.Image.Height)
                        RC = new Rectangle(new Point(i * pictureBox1.Image.Width / H, j * pictureBox1.Image.Height / V), new Size(pictureBox1.Image.Width / H, pictureBox1.Image.Height - j * pictureBox1.Image.Height / V));
                    else
                        if (i * pictureBox1.Image.Width / H + pictureBox1.Image.Width / H > pictureBox1.Image.Width && j * pictureBox1.Image.Height / V + pictureBox1.Image.Height / V > pictureBox1.Image.Height)
                        RC = new Rectangle(new Point(i * pictureBox1.Image.Width / H, j * pictureBox1.Image.Height / V), new Size(pictureBox1.Image.Width - i * pictureBox1.Image.Width / H, pictureBox1.Image.Height - j * pictureBox1.Image.Height / V));
                    else
                        RC = new Rectangle(new Point(i * pictureBox1.Image.Width / H, j * pictureBox1.Image.Height / V), new Size(pictureBox1.Image.Width / H, pictureBox1.Image.Height / V));
                    Bitmap CuttedImage = CutImage((Bitmap)pictureBox1.Image, RC);
                    CuttedImage.Save(saveFileDialog.FileName + l.ToString(), System.Drawing.Imaging.ImageFormat.Gif);
                    l++;
                }

            MessageBox.Show("Изображение успешно разрезано", "Все круто!", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        public Bitmap CutImage(Bitmap SRC, Rectangle RC)
        {

            Bitmap bmp = new Bitmap(RC.Width, RC.Height);;
            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.Transparent);
            g.DrawImage(SRC, 0, 0, RC, GraphicsUnit.Pixel);
            
            return bmp;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
