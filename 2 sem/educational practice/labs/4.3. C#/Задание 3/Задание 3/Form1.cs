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

namespace Задание_3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        OpenFileDialog openFileDialog = new OpenFileDialog();
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
        private void chooseFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Filter = "Text files (*.txt) |*.txt|All files (*.*) |*.*";
            openFileDialog.FilterIndex = 0;
            openFileDialog.DefaultExt = "txt";
            openFileDialog.FileName = "*.txt*";

            openFileDialog.RestoreDirectory = true;
            openFileDialog.Multiselect = false;

            openFileDialog.ShowDialog();
        }

        private void chooseOutputFolderToolStripMenuItem_Click(object sender, EventArgs e)
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
                saveFileDialog.DefaultExt = "txt";
                saveFileDialog.FileName = "Out";
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача 3\nАлина Крагель, 1 курс, 10 группа, 10.04.2020", "О программе...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog.FileName == "")
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                    return;
            if (saveFileDialog.FileName == "")
                if (folderBrowserDialog.ShowDialog(this) == DialogResult.OK)
                {
                    MessageBox.Show("Выбранная для сохранения папка: " + folderBrowserDialog.SelectedPath);
                    folderBrowserDialog.ShowNewFolderButton = false;
                    folderBrowserDialog.SelectedPath = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                    folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
                    saveFileDialog.InitialDirectory = folderBrowserDialog.SelectedPath;
                    System.IO.Directory.SetCurrentDirectory(folderBrowserDialog.SelectedPath);
                    saveFileDialog.DefaultExt = "txt";
                    saveFileDialog.FileName = "Out";
                    return;
                }
            using (StreamWriter fOut = new StreamWriter(saveFileDialog.FileName))
            {
                using (StreamReader fIn = new StreamReader(openFileDialog.FileName))
                {
                    int sArr = Convert.ToInt32(fIn.ReadLine());
                    string[] arrString = fIn.ReadLine().Split();
                    int[] intArray = new int[sArr], finalArray = new int[sArr];
                    for (int i = 0; i < sArr; i++)
                        intArray[i] = Convert.ToInt32(arrString[i]);
                    intArray = BetchSort(intArray);
                    fOut.WriteLine(sArr);
                    string Str = "";
                    for (int i = 0; i < sArr; i++)
                        Str += intArray[i] + " ";
                    fOut.WriteLine(Str);
                    MessageBox.Show("Сортировка массива завершена успешно.");
                }
            }
        }

        static int[] Sorting(int[] firstHalfArray, int[] secondHalfArray)
        {
            int[] finalArr = new int[firstHalfArray.Length + secondHalfArray.Length];
            int a = 0, b = 0;
            for (int i = 0; i < firstHalfArray.Length + secondHalfArray.Length; i++)
            {
                if (b < secondHalfArray.Length && a < firstHalfArray.Length)
                    if (firstHalfArray[a] > secondHalfArray[b])
                        finalArr[i] = secondHalfArray[b++];
                    else
                        finalArr[i] = firstHalfArray[a++];
                else
                    if (b < secondHalfArray.Length)
                    finalArr[i] = secondHalfArray[b++];
                else
                    finalArr[i] = firstHalfArray[a++];
            }
            return finalArr;
        }

        static int[] BetchSort(int[] Array)
        {
            if (Array.Length == 1)
                return Array;
            int mArr = Array.Length / 2;
            return Sorting(BetchSort(Array.Take(mArr).ToArray()), BetchSort(Array.Skip(mArr).ToArray()));
        }
    }
}
