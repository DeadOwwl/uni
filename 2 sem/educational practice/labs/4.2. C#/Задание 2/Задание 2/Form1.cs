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

namespace Задание_2
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        OpenFileDialog openFileDialog = new OpenFileDialog();
        private void chooseInputToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Text files (*.txt) |*.txt|All files (*.*) |*.*";
            openFileDialog.FilterIndex = 0;
            openFileDialog.DefaultExt = "txt";
            openFileDialog.FileName = "*.txt*";

            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            openFileDialog.ShowDialog();
        }
        FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
        SaveFileDialog closeFileDialog = new SaveFileDialog();
        private void chooseOutputFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog())
            {
                folderBrowserDialog.ShowNewFolderButton = false;
                folderBrowserDialog.SelectedPath = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
                if (folderBrowserDialog.ShowDialog(this) == DialogResult.OK)
                    MessageBox.Show("Выбрання для сохранения папка: " + folderBrowserDialog.SelectedPath);
                closeFileDialog.InitialDirectory = folderBrowserDialog.SelectedPath;
                System.IO.Directory.SetCurrentDirectory(folderBrowserDialog.SelectedPath);
                closeFileDialog.DefaultExt = "txt";
                closeFileDialog.FileName = "Out";
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача 2\nАлина Крагель, 1 курс, 10 группа, 03.04.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private byte[] sKey = new byte[128];
        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog.FileName == "")
                if (openFileDialog.ShowDialog() != DialogResult.OK)
                    return;
            if (closeFileDialog.FileName == "")
                if (folderBrowserDialog.ShowDialog(this) != DialogResult.OK)
                    return;

            Random rand = new Random();
            for (int i=0; i < 128; i++)
                sKey[i] = (byte)rand.Next();

            using (FileStream fOut = new FileStream(closeFileDialog.FileName, FileMode.Create))
            {
                using (BinaryReader fRead = new BinaryReader(File.Open(openFileDialog.FileName, FileMode.OpenOrCreate)))
                {
                    int rBytes = 0;
                    fOut.Write(sKey, 0, 128);
                    byte[] tBlock = new byte[512];
                    while (fRead.Read(tBlock, 0, 512) != 0)
                    {
                        for (int i = 0; i < 512; i++)
                        {
                            for (int j = 0; j < 128; j++)
                            {
                                int cT = tBlock[i], cB = sKey[j % sKey.Length];
                                cT = cT ^ cB;
                                tBlock[i] = (byte)cT;
                            }
                        }
                        fOut.Write(tBlock, 0, 512);
                        rBytes++;
                    }
                    if (fRead.BaseStream.Position!= fRead.BaseStream.Length)
                    {
                        byte[] bOther = new byte[fRead.BaseStream.Length - fRead.BaseStream.Position];
                        fRead.Read(bOther, 0, (int)(fRead.BaseStream.Length - fRead.BaseStream.Position));
                        for (int i = 0; i < 512; i++)
                        {
                            int cT = bOther[i], cB = sKey[i % sKey.Length];
                            cT = cT ^ cB;
                            bOther[i] = (byte)cT;
                            fOut.Write(bOther, 0, (int)(fRead.BaseStream.Length - fRead.BaseStream.Position));
                        }
                    }
                }
            }
            MessageBox.Show("Файл зашифрован", "О выполнении", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
