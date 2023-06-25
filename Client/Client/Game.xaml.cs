using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading;
using System.Windows.Shapes;
using System.ComponentModel;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Xml.Linq;
using System.Windows.Threading;
using System.Drawing;

namespace Client
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        int id = 0;
        GetQuestionResponse res = null;
        private int timerSeconds = 0;
        private DispatcherTimer timer;
        private int numq = 0;
        private int gotRight = 0;
        private int _time = 0;
        bool unAnswered = true;
        bool midAnswer = false;
        SubmitAnswerResponse ans = null;
        BackgroundWorker bgWorker = new BackgroundWorker();
        bool _quiet;
        public Game(bool quiet, int time, int numOfQuestion, int right)
        {
            _quiet = quiet;
            InitializeComponent();
            timerSeconds = time;
            numq = numOfQuestion;
            gotRight = right;
            _time = time;
            Rignt.Text = right.ToString();
            Left.Text = numOfQuestion.ToString();
            timeTxt.Text = time.ToString();
            bgWorker.WorkerSupportsCancellation = true;
            bgWorker.WorkerReportsProgress = true;
            bgWorker.ProgressChanged += actualWork;
            bgWorker.DoWork += work;

            ask();

        }
        void work(object sender, DoWorkEventArgs e)
        {
            unAnswered = false;
            midAnswer = true;
            string msg = Convert.ToString(17, 2);
            msg = Translations.padLeft(msg, 8);
            string json = JsonConvert.SerializeObject(new SubmitAnswerRequest(id));
            msg += Translations.padLeft(Convert.ToString(json.Length, 2), 32);
            msg += Translations.stringToBinary(json);
            NetworkStream clientStream = Communicator.client.GetStream();
            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            byte[] code = new byte[8];
            int bytesRead = clientStream.Read(code, 0, 8);
            string code_str = System.Text.Encoding.Default.GetString(code);
            byte[] size = new byte[32];
            bytesRead = clientStream.Read(size, 0, 32);
            string size_str = System.Text.Encoding.Default.GetString(size);
            byte[] rooms = new byte[Convert.ToInt32(size_str, 2) * 8];
            bytesRead = clientStream.Read(rooms, 0, Convert.ToInt32(size_str, 2) * 8);
            string rooms_str = System.Text.Encoding.Default.GetString(rooms);
            if (Convert.ToInt32(code_str, 2) == 1)
            {
                ans = JsonConvert.DeserializeObject<SubmitAnswerResponse>(Translations.binaryToString(rooms_str));
                if (ans.correctAns == id)
                {
                    gotRight++;
                }
            }
            bgWorker.ReportProgress(0);

        }
        void actualWork(object sender, ProgressChangedEventArgs e)
        {
            timer.Stop();
            if (numq == 0)
            {
                EndScreen finish = new EndScreen();
                this.Close();
                finish.ShowDialog();

            }
            Game next = new Game(_quiet, _time, numq - 1, gotRight);
            this.Close();
            next.ShowDialog();
        }
    private void ask()
    {
            string msg = Convert.ToString(16, 2);
            msg = Translations.padLeft(msg, 8);
            msg += Translations.padLeft("", 32);
            NetworkStream clientStream = Communicator.client.GetStream();
            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            StartTimer();
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            byte[] code = new byte[8];
            int bytesRead = clientStream.Read(code, 0, 8);
            string code_str = System.Text.Encoding.Default.GetString(code);
            byte[] size = new byte[32];
            bytesRead = clientStream.Read(size, 0, 32);
            string size_str = System.Text.Encoding.Default.GetString(size);
            byte[] rooms = new byte[Convert.ToInt32(size_str, 2) * 8];
            bytesRead = clientStream.Read(rooms, 0, Convert.ToInt32(size_str, 2) * 8);
            string rooms_str = System.Text.Encoding.Default.GetString(rooms);
            if (Convert.ToInt32(code_str, 2) == 1)
            {
                res = JsonConvert.DeserializeObject<GetQuestionResponse>(Translations.binaryToString(rooms_str));
                question.Text = res.question;
                ans1.Content = res.answer[0];
                ans2.Content = res.answer[1];
                ans3.Content = res.answer[2];
                ans4.Content = res.answer[3];
            }
            
    }
        



        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            StartTimer();
        }

        private void StartTimer()
        {
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            timerSeconds--;
            if(timerSeconds > 0)
            {
                timeTxt.Text = timerSeconds.ToString();
            }
            if (timerSeconds <= 0)
            {
                timer.Stop();
                if (unAnswered)
                {
                    id = 5;
                    bgWorker.RunWorkerAsync();
                }
            }
        }



        private int getID(string ans)
        {
            
            for (int i = 0; i < res.answer.Length; i++)
            {
                if(ans == res.answer[i])
                {
                    return i;
                }
            }
            return -1;
        }
        private void ans1_clicked(object sender, RoutedEventArgs e)
        {
            if(!midAnswer)
            {

                id = getID(ans1.Content.ToString());
                ans1.IsEnabled = false;
                bgWorker.RunWorkerAsync();

            }
            

        }
        private void ans2_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                id = getID(ans2.Content.ToString());
                ans2.IsEnabled = false;
                bgWorker.RunWorkerAsync();
            }
            
        }
        private void ans3_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                id = getID(ans3.Content.ToString());
                ans3.IsEnabled = false;
                bgWorker.RunWorkerAsync();
            }
            
        }
        private void ans4_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                id = getID(ans4.Content.ToString());
                ans4.IsEnabled = false;
                bgWorker.RunWorkerAsync();

            }
            
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            string msg = Convert.ToString(19, 2);
            msg = Translations.padLeft(msg, 8);
            msg += Translations.padLeft("", 32);
            NetworkStream clientStream = Communicator.client.GetStream();

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
            byte[] code = new byte[8];
            int bytesRead = clientStream.Read(code, 0, 8);
            string code_str = System.Text.Encoding.Default.GetString(code);
            byte[] size = new byte[32];
            bytesRead = clientStream.Read(size, 0, 32);
            string size_str = System.Text.Encoding.Default.GetString(size);
            byte[] rooms = new byte[Convert.ToInt32(size_str, 2) * 8];
            bytesRead = clientStream.Read(rooms, 0, Convert.ToInt32(size_str, 2) * 8);
            string rooms_str = System.Text.Encoding.Default.GetString(rooms);
            if (Convert.ToInt32(code_str, 2) == 1)
            {
                Menu menu = new Menu(_quiet);
                this.Close();
                menu.ShowDialog();

            }

        }
    }
}
