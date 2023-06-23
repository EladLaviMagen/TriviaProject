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

namespace Client
{
    /// <summary>
    /// Interaction logic for AdminRoom.xaml
    /// </summary>
    public partial class AdminRoom : Window
    {
        GetRoomStateResponse response = null;
        bool _admin = false;
        BackgroundWorker bgWorker = new BackgroundWorker();

        public AdminRoom(bool admin)
        {
            _admin = admin;
            InitializeComponent();
            if(!admin)
            {
                Start.Visibility = Visibility.Collapsed;
                Start.IsEnabled = false;
                close.Content = "Leave room";
            }
            bgWorker.WorkerSupportsCancellation = true;
            bgWorker.WorkerReportsProgress = true;
            bgWorker.ProgressChanged += actualWork;
            bgWorker.DoWork += work;
            bgWorker.RunWorkerAsync();
        }

        void work(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                string msg = Convert.ToString(13, 2);
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
                response = JsonConvert.DeserializeObject<GetRoomStateResponse>(Translations.binaryToString(rooms_str));
                if(response.status == 1)
                {
                    if(response.players != null)
                    {
                        bgWorker.ReportProgress(0);
                        
                    }
                }
                Thread.Sleep(1000);

            }
        }
        void actualWork(object sender, ProgressChangedEventArgs e)
        {
            membersList.Items.Clear();
            for (int i = 0; i < response.players.Length; i++)
            {
                membersList.Items.Add(response.players[i]);
            }
        }
        private void membersList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
