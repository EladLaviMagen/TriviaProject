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

namespace Client
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        GetQuestionResponse res = null;
        private int timerSeconds = 0;
        private DispatcherTimer timer;
        private int numq = 0;
        private int gotRight = 0;
        private int _time = 0;
        bool unAnswered = true;
        bool midAnswer = false;
        SubmitAnswerResponse ans = null;
        public Game(int time, int numOfQuestion, int right)
        {
            InitializeComponent();
            timerSeconds = time;
            numq = numOfQuestion;
            gotRight = right;
            _time = time;
            Rignt.Text = right.ToString();
            Left.Text = numOfQuestion.ToString();
            timeTxt.Text = time.ToString();
            ask();

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
            if(Convert.ToInt32(code_str, 2) == 1)
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
                    answer(5);

                }
                if (ans.correctAns == 0)
                {
                    ans1.Content = ans1.Content + " CORRECT";
                }
                else if (ans.correctAns == 1)
                {
                    ans2.Content = ans2.Content + " CORRECT";
                }
                else if (ans.correctAns == 2)
                {
                    ans3.Content = ans3.Content + " CORRECT";
                }
                else if (ans.correctAns == 3)
                {
                    ans4.Content = ans4.Content + " CORRECT";
                }
                timer.Start();
            }
            if(timerSeconds <= -5)
            {
                timer.Stop();
                if (numq == 0)
                {
                    EndScreen finish = new EndScreen();
                    this.Close();
                    finish.ShowDialog();

                }
                Game next = new Game(_time, numq - 1, gotRight);
                this.Close();
                next.ShowDialog();
            }
        }

        private void answer(int id)
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
            if(Convert.ToInt32(code_str, 2) == 1)
            {
                ans = JsonConvert.DeserializeObject<SubmitAnswerResponse>(Translations.binaryToString(rooms_str));
                if (ans.correctAns == id)
                {
                    gotRight++;
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
                answer(getID(ans1.Content.ToString()));
            }
            

        }
        private void ans2_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                answer(getID(ans2.Content.ToString()));
            }
            
        }
        private void ans3_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                answer(getID(ans3.Content.ToString()));
            }
            
        }
        private void ans4_clicked(object sender, RoutedEventArgs e)
        {
            if (!midAnswer)
            {
                answer(getID(ans4.Content.ToString()));

            }
            
        }
    }
}
