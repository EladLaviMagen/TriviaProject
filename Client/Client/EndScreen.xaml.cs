using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Threading;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.ComponentModel;
using System.Timers;

namespace Client
{
    /// <summary>
    /// Interaction logic for EndScreen.xaml
    /// </summary>
    public partial class EndScreen : Window
    {
        bool _quiet = true;
        BackgroundWorker bgWorker = new BackgroundWorker();
        GetGameResultsResponse res = null;

        /*
         * Most aspects here are explained in the menu and signup however just to explain why I used a thread here
         * Windows are a bit problematic, as for they need to be "active", and a screen doesn't build itself until 
         * it's contructor is done, so to give it an easier time and to give the users a nicer time while playing
         * I used a thread to allow the window to open quick, the results are a bit delayed however
        */
        public EndScreen(bool quiet)
        {
            _quiet = quiet;
            bgWorker.WorkerSupportsCancellation = true;
            bgWorker.WorkerReportsProgress = true;
            bgWorker.ProgressChanged += actualWork;
            bgWorker.DoWork += work;
            bgWorker.RunWorkerAsync();
            InitializeComponent();
            Thread.Sleep(3000);
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

    void work(object sender, DoWorkEventArgs e)
    {
        //Getting results
        string msg = Convert.ToString(18, 2);
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
                //Displaying
            res = JsonConvert.DeserializeObject<GetGameResultsResponse>(Translations.binaryToString(rooms_str));
            bgWorker.ReportProgress(0);

        }
    }

        void actualWork(object sender, ProgressChangedEventArgs e)
        {
            //Updating visuals
            PlayerResults[] arr = new PlayerResults[res.results.Length / 4];
            for (int i = 0; i < res.results.Length / 4; i++)
            {
                arr[i] = new PlayerResults(res.results[i * 4], float.Parse(res.results[i * 4 + 1]), int.Parse(res.results[i * 4 + 2]), int.Parse(res.results[i * 4 + 3]));
            }
            int max = 0;
            for (int i = 0; i < arr.Length; i++)
            {
                if (arr[i].correctAnswerCount > max)
                {
                    max = arr[i].correctAnswerCount;
                }
            }
            resultsView.Items.Clear();
            for (int i = 0; i < arr.Length; i++)
            {
                if (arr[i].correctAnswerCount == max)
                {
                    arr[i].username += " WINNER!";
                }
                resultsView.Items.Add("AAT - " + arr[i].averageAnswerTime + " R - " + arr[i].correctAnswerCount + " W - " + arr[i].answerTimeout + " " + arr[i].username);
            }

        }
        private void leave_Click(object sender, RoutedEventArgs e)
        {
            //Leaving
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
