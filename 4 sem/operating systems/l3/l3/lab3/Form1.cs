using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace l3
{
    public partial class Form1 : Form
    {

        bool isChecking = true;
        bool isSolving= true;
        static List<string> inputFilesNames = new List<string>();
        static Queue<string> queueInputFilesNames = new Queue<string>();
        static List<bool> inputFilesCheker = new List<bool>();
        static Queue<(string,List<Tuple<string, string>>)> queueListConditions = new Queue<(string,List<Tuple<string, string>>)>();
        static Queue<string> queueListAnswers = new Queue<string>();
        static List<string> outputFilesNames = new List<string>();
        static List<string> myOutputFilesNames = new List<string>();
        static List<bool> checkerWithEtalons = new List<bool>();

        Thread readerCheckThread;
        Thread solveThread;
        Thread checkerThread;

        //алгоритм
        public static List<string> cipherChecking(List<Tuple<string, string>> lTuples)
        {
            List<string> aTestAnswers = new List<string>();
            for (int k = 0; k < lTuples.Count; k++)
            {
                string s1 = lTuples[k].Item1;
                string s2 = lTuples[k].Item2;

                string answer = "YES";
                if (s1.Length != s2.Length)
                    answer = "NO";
                else
                {
                    List<int> s1_symbols_count = new List<int>();
                    List<int> s2_symbols_count = new List<int>();
                    for (int i = 0; i < s1.Length; i++)
                    {
                        s1_symbols_count.Add(0);
                        for (int j = i + 1; j < s1.Length; j++)
                        {
                            if (s1[i] == s1[j])
                                s1_symbols_count[i]++;
                        }
                    }
                    for (int i = 0; i < s2.Length; i++)
                    {
                        s2_symbols_count.Add(0);
                        for (int j = i + 1; j < s2.Length; j++)
                        {
                            if (s2[i] == s2[j])
                                s2_symbols_count[i]++;
                        }
                    }
                    s1_symbols_count.Sort();
                    s2_symbols_count.Sort();
                    for (int i = 0; i < s1.Length; i++)
                        if (s1_symbols_count[i] != s2_symbols_count[i])
                            answer = "NO";
                    aTestAnswers.Add(answer);
                }
            }
            return aTestAnswers;
        }

        public Form1()
        {
            InitializeComponent();
        }

        //проверка очередного теста на правильность входных данных
        private static void filesCheck(string fileName)
        {
            StreamReader fin = new StreamReader(new FileStream(fileName, FileMode.Open));
            bool flag = true;
            int k = int.Parse(fin.ReadLine());
            List<Tuple<string, string>> l = new List<Tuple<string, string>>();
            if (k < 1 || k > 5)
                flag = false;
            else
            {
                int numString = 0;
                String line;
                while ((line = fin.ReadLine()) != null)
                {
                    string s1 = line;
                    string s2;
                    if ((s2 = fin.ReadLine()) == null)
                    {
                        flag = false;
                        break;
                    }
                    if (s1.Length > 100 || s2.Length > 100)
                    {
                        flag = false;
                        break;
                    }
                    numString += 2;
                    l.Add(new Tuple<string, string>(s1, s2));
                }
                if (numString != 2 * k)
                    flag = false;
            }
            fin.Close();
            inputFilesCheker.Add(flag);

            if (flag)
            {
                queueListConditions.Enqueue((fileName,l));
            }
        }

        //запись ответов
        public static void writeAnswer(String fileName, List<string> answer)
        {

            StreamWriter sw = new StreamWriter(new FileStream(fileName, FileMode.Create));
            for (int j = 0; j < answer.Count; j++)
            {
                sw.WriteLine(answer[j]);
            }
            sw.Close();
            queueListAnswers.Enqueue(fileName);
        }

        //проверка с эталонными
        private void checkWithEtalons(string fname)
        {
            if (outputFilesNames.Count == 0)
                return;

            string et = fname.Substring(0, fname.Length - 11) + ".out";
            string inp = fname.Substring(0, fname.Length - 11) + ".in";

            var a1 = File.ReadAllText(fname);
            var a2 = File.ReadAllText(et);

            bool flag = true;
            if (a1.Length == a2.Length) {
                for (int j = 0; j < a1.Length; j++)
                {
                    if (a1[j] != a2[j])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            MethodInvoker methodInvokerDelegate = delegate () {
                if (flag)
                {
                    textBox1.AppendText("Program input file: \n" + "   " + inp + "\nProgram output file: \n" + "   " + fname + ",\nReference file: \n" + "   " + et + "\n" + "State: \n   Success");
                }
                else
                {
                    textBox1.AppendText("Program input file: \n" + "   " + inp + "\nProgram output file: \n" + "   " + fname + ",\nReference file: \n" + "   " + et + "\n" + "State: \n   Fail");
                }
            };


            textBox1.Invoke(methodInvokerDelegate);



            //StreamReader sr = new StreamReader(new FileStream(outputFilesNames[0], FileMode.Open));
            //outputFilesNames.RemoveAt(0);
            //string line;
            //int i = 0;
            //flag = true;
            //while ((line = sr.ReadLine()) != null)
            //{
            //    if (!line.Equals(fname[i]))
            //    {
            //        flag = false;
            //        break;
            //    }
            //    i++;
            //}
            //checkerWithEtalons.Add(flag);
            //sr.Close();
        }

        //выбор дирректории и создание инпутов и аутпутов (стринг)
        private void button1_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog startDialog = new FolderBrowserDialog();
            startDialog.ShowDialog();
            Directory.GetFiles(startDialog.SelectedPath).ToList().ForEach(file =>
            {
                if (file.ToLower().EndsWith(".in"))
                {
                    inputFilesNames.Add(file);
                    queueInputFilesNames.Enqueue(file);
                    //позже перепиши в один контейнер
                }
            });
            for (int i = 0; i < inputFilesNames.Count; i++)
            {
                outputFilesNames.Add(inputFilesNames[i].Substring(0, inputFilesNames[i].Length - 3) + ".out");
                myOutputFilesNames.Add(inputFilesNames[i].Substring(0, inputFilesNames[i].Length - 3) + " answer.out");
            }
            MessageBox.Show("Import has been successfully completed.", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        //погнали
        private void button2_Click(object sender, EventArgs e)
        {
            readerCheckThread = new Thread(() => {
                while (queueInputFilesNames.Count > 0)
                {
                    Monitor.Enter(queueInputFilesNames);
                    string fileName = queueInputFilesNames.Dequeue();
                    Monitor.Exit(queueInputFilesNames);
                    filesCheck(fileName);
                }
                isChecking = false;
            });
            readerCheckThread.Start();

            solveThread = new Thread(() =>
            {
                while (isSolving)
                {
                    if (queueListConditions.Count == 0)
                    {
                        if (isChecking)
                            continue;
                        else
                            break;
                    }
                    while (isChecking || queueListConditions.Count > 0)
                    {
                        Monitor.Enter(queueListConditions);
                        if (queueListConditions.Count > 0)
                        {
                            (string filename, List<Tuple<string, string>> aCondition) = queueListConditions.Dequeue();
                            Monitor.Exit(queueListConditions);
                            List<string> anAnswer = cipherChecking(aCondition);
                            Monitor.Enter(queueListAnswers);
                            filename = filename.Substring(0, filename.Length - 3) + " answer.out";

                            writeAnswer(filename, anAnswer);
                            Monitor.Exit(queueListAnswers);
                        }
                        else
                            Monitor.Exit(queueListConditions);
                    }
                }
                isSolving = false;
            });
            solveThread.Start();

            checkerThread = new Thread(() =>
            {
                while (isSolving || isChecking || queueListAnswers.Count > 0)
                {
                    Monitor.Enter(queueListAnswers);
                    if (queueListAnswers.Count > 0)
                    {

                        string fname = queueListAnswers.Dequeue();
                        Monitor.Exit(queueListAnswers);
                        checkWithEtalons(fname);
                        /*                        Monitor.Enter(queueListAnswers);
                                                queueListAnswers.Enqueue(anAnswer);
                                                Monitor.Exit(queueListAnswers);*/
                    }
                    else
                        Monitor.Exit(queueListAnswers);
                }

            });

            checkerThread.Start();
            

/*            readerCheckThread.Start();
            solveThread.Start();
            checkerThread.Start();*/

        }

        private void button3_Click(object sender, EventArgs e)
        {
            isSolving = false;
        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
