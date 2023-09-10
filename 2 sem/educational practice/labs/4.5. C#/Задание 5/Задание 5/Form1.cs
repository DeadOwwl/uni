using System;
using System.IO;
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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            PictList = new List<PictureBox>();
            InformationList = new List<string>();
        }

        OpenFileDialog openFileDialog = new OpenFileDialog();
        FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
        SaveFileDialog saveFileDialog = new SaveFileDialog();

        Rectangle selRect;
        Point orig;
        Pen pen = new Pen(Brushes.Red, 0.5f) { DashStyle = System.Drawing.Drawing2D.DashStyle.Dash };

        List<PictureBox> PictList;
        static List <string> InformationList;

        public void AddLInf(string str)
        {
            InformationList.Add(str);
        }

        void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            bool flag = true;
            pictureBox1.Paint -= Selection_Paint;
            pictureBox1.Paint += pictureBox1_Paint;
            pictureBox1.Invalidate();

            for (int i=0; i<PictList.Count;i++)
            {
                Rectangle pictRect = new Rectangle();
                pictRect.X = PictList[i].Location.X;
                pictRect.Y = PictList[i].Location.X;
                pictRect.Width = PictList[i].Width;
                pictRect.Height = PictList[i].Height;

                if ((selRect.X > PictList[i].Location.X && selRect.X < PictList[i].Location.X + PictList[i].Width && selRect.Y > PictList[i].Location.Y && selRect.Y < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X + selRect.Width > PictList[i].Location.X && selRect.X + selRect.Width < PictList[i].Location.X + PictList[i].Width && selRect.Y + selRect.Height > PictList[i].Location.Y && selRect.Y + selRect.Height < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X > PictList[i].Location.X && selRect.X + selRect.Width < PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.Y > PictList[i].Location.Y && selRect.Y + selRect.Height < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X && selRect.X + selRect.Width < PictList[i].Location.X + PictList[i].Width && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height && selRect.Y > PictList[i].Location.Y && selRect.Y < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.X > PictList[i].Location.X && selRect.X < PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y && selRect.Y + selRect.Height > PictList[i].Location.Y && selRect.Y + selRect.Height < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.Y > PictList[i].Location.Y && selRect.Y < PictList[i].Location.Y + PictList[i].Height && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X > PictList[i].Location.X && selRect.X < PictList[i].Location.X + PictList[i].Width && selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y  && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y && selRect.Y + selRect.Height > PictList[i].Location.Y  && selRect.Y + selRect.Height < PictList[i].Location.Y + PictList[i].Height) ||
                    (selRect.X < PictList[i].Location.X && selRect.X + selRect.Width > PictList[i].Location.X  && selRect.X + selRect.Width < PictList[i].Location.X + PictList[i].Width && selRect.Y < PictList[i].Location.Y && selRect.Y + selRect.Height > PictList[i].Location.Y + PictList[i].Height) ||
                    selRect.X<0 || selRect.X > pictureBox1.Width || selRect.Y < 0 || selRect.Y > pictureBox1.Height || selRect.X + selRect.Width < 0 || selRect.X + selRect.Width > pictureBox1.Width || selRect.Y + selRect.Height < 0 || selRect.Y + selRect.Height > pictureBox1.Height)
                {
                    flag = false;
                    break;
                }
            }

            if (flag==true)
            {

                PictureBox PB = new PictureBox();
                PB.Parent = pictureBox1;
                PB.Location = selRect.Location;
                PB.Size = selRect.Size;
                // PB.Visible = false; 

                PictList.Add(PB);

                Form2 FS = new Form2();
                FS.ShowDialog();
            }
            else
            {
                MessageBox.Show("Выделенная облаcть не может пересекаться с заданной ранне областью или выходить за границы бокса.", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void ImageWindow_Paint(object sender, PaintEventArgs pe)
        {
                Paint -= ImageWindow_Paint;
                if (openFileDialog.FileName != "")
                {
                    pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
                    Bitmap SrcImg = new Bitmap(Image.FromFile(openFileDialog.FileName), pictureBox1.Width, pictureBox1.Height);
                    pictureBox1.BackgroundImage = SrcImg;
                }
        }

        void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            pictureBox1.Paint -= pictureBox1_Paint;
            pictureBox1.Paint += Selection_Paint;
            orig = e.Location;
        }

        private void Selection_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(pen, selRect);
            e.Graphics.FillRectangle(Brushes.Red, selRect);
            e.Dispose();
        }

        void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            selRect = GetSelRectangle(orig, e.Location);
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                (sender as PictureBox).Refresh();
        }

        void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Red, selRect);
            e.Graphics.FillRectangle(Brushes.Red, selRect);
        }

        Rectangle GetSelRectangle(Point orig, Point location)
        {
            int deltaX = location.X - orig.X, deltaY = location.Y - orig.Y;
            Size sizeOfRectangle = new Size(Math.Abs(deltaX), Math.Abs(deltaY));
            Rectangle rect = new Rectangle();
            if (deltaX >= 0 & deltaY >= 0)
                rect = new Rectangle(orig, sizeOfRectangle);
            if (deltaX < 0 & deltaY > 0)
                rect = new Rectangle(location.X, orig.Y, sizeOfRectangle.Width, sizeOfRectangle.Height);
            if (deltaX < 0 & deltaY < 0)
                rect = new Rectangle(location, sizeOfRectangle);
            if (deltaX > 0 & deltaY < 0)
                rect = new Rectangle(orig.X, location.Y, sizeOfRectangle.Width, sizeOfRectangle.Height);
            return rect;
        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Image files (*.BMP, *.JPG, *.PNG, *.GIF) |*.BMP; *.JPG; *.PNG; *.GIF|All files (*.*) |*.*";
            openFileDialog.FilterIndex = 0;

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

            if (openFileDialog.FileName != "")
            {
                Paint += ImageWindow_Paint;
                Invalidate();
                pictureBox1.Paint += pictureBox1_Paint;
                pictureBox1.MouseMove += pictureBox1_MouseMove;
                pictureBox1.MouseUp += pictureBox1_MouseUp;
                pictureBox1.MouseDown += pictureBox1_MouseDown;
            }
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
                saveFileDialog.DefaultExt = "html";
                saveFileDialog.FileName = "Final Map";
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача 5\nАлина Крагель, 1 курс, 10 группа, 10.04.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
                    MessageBox.Show("Ошибка открытия выбранного файла", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            if (openFileDialog.FileName != "")
            {
                pictureBox1.Paint += pictureBox1_Paint;
                pictureBox1.MouseMove += pictureBox1_MouseMove;
                pictureBox1.MouseUp += pictureBox1_MouseUp;
                pictureBox1.MouseDown += pictureBox1_MouseDown;
            }
        }

        string mainString;

        private void button2_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.FileName == "")
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
                    saveFileDialog.DefaultExt = "html";
                    saveFileDialog.FileName = "Final Map";
                }
            }
            using (StreamWriter outFile = new StreamWriter(saveFileDialog.FileName))
            {
                outFile.Write(mainString);
            }
            mainString = "";
            MessageBox.Show("HTML-карта успешно сохранена.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
            for (int i = 0; i < PictList.Count; i++)
                PictList[i].Dispose();
            PictList.Clear();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            mainString = "<html>\n<body>\n<img src = \"" + openFileDialog.FileName + "\"width=\""+pictureBox1.Image.Width+"\" height=\""+ pictureBox1.Image.Height + "\" usemap=" + "\"#mapname\" border =\"0\">\n<map name = \"mapname\">";

            for (int i = 0; i < PictList.Count; i++)
            {
                String[] Information = InformationList[i].Split('|');
                String Coordinates = "";

                Coordinates += PictList[i].Location.X.ToString() + ",";
                Coordinates += PictList[i].Location.Y.ToString() + ",";
                Coordinates += (PictList[i].Location.X + PictList[i].Width).ToString() + ",";
                Coordinates += (PictList[i].Location.Y + PictList[i].Height).ToString();

                mainString += "\n<area shape = \"rect\" coords = \"" + Coordinates + "\" href = \"" + Information[1] + "\" alt= \"" + Information[0] + "\">";
            }

            MessageBox.Show("HTML-карта успешно создана.", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);

            mainString += "\n</map>\n</body>\n</html>";
        }
    }
}
