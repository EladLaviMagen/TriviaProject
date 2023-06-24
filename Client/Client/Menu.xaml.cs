using Microsoft.Win32;
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
using System.Threading;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;
using System.Windows.Media;
using System.IO;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Controls.Primitives;
using System.Runtime.CompilerServices;

namespace Client
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        BackgroundWorker bgWorker = new BackgroundWorker();
        bool stopFlag = false;
        RoomData[] roomdatas = null;
        bool _quiet = false;
        public Menu(bool quiet)
        {
            _quiet = quiet;
            InitializeComponent();
            if (!quiet)
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
                openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\theme.mp3";
                Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
                Audio.mediaPlayer.Play();
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
                string msg = Convert.ToString(9, 2);
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
                GetRoomsResponse response = JsonConvert.DeserializeObject<GetRoomsResponse>(Translations.binaryToString(rooms_str));
                roomdatas = new RoomData[response.rooms.Length / 6];
                for (int i = 0; i < response.rooms.Length / 6; i++)
                {
                    roomdatas[i] = new RoomData(int.Parse(response.rooms[i * 6]), response.rooms[i * 6 + 1], int.Parse(response.rooms[i * 6 + 2]), int.Parse(response.rooms[i * 6 + 3]), int.Parse(response.rooms[i * 6 + 4]), int.Parse(response.rooms[i * 6 + 5]));
                }
                bgWorker.ReportProgress(0);
                if (stopFlag)
                {
                    bgWorker.CancelAsync();
                    stopFlag = false;
                    
                }
                if (bgWorker.CancellationPending)
                {
                    return;
                }
                Thread.Sleep(1000);

            }
        }
        void actualWork(object sender, ProgressChangedEventArgs e)
        {
            string selected = "";
            if (listBox.SelectedItem != null)
            {
                selected = listBox.SelectedItem.ToString();
            }
            listBox.Items.Clear();
            for (int i = 0; i < roomdatas.Length; i++)
            {
                
                if (roomdatas[i].isActive == 0)
                {
                    string item = roomdatas[i].id + " " + roomdatas[i].name;
                    listBox.Items.Add(item);
                    if (item == selected)
                    {
                        listBox.SelectedItem = selected;
                    }
                }
                
            }
        }
        

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }


        private void ready_Click(object sender, RoutedEventArgs e)
        {
            stopFlag = true;
            while (stopFlag)
            { }
            if (listBox.SelectedItem != null)
            {
                string msg = Convert.ToString(5, 2);
                msg = Translations.padLeft(msg, 8);
                string select = listBox.SelectedItem.ToString();
                string keeper = "";
                int i = 0;
                while (select[i] != ' ')
                {
                    keeper+= select[i];
                    i++;
                }
                string json = JsonConvert.SerializeObject(new JoinRoomRequest(int.Parse(keeper)));
                msg += Translations.padLeft(Convert.ToString(json.Length, 2), 32);
                msg += Translations.stringToBinary(json);
                NetworkStream clientStream = Communicator.client.GetStream();
                byte[] buffer = new ASCIIEncoding().GetBytes(msg);
                clientStream.Write(buffer, 0, buffer.Length);

                byte[] code = new byte[8];
                int bytesRead = clientStream.Read(code, 0, 8);
                string code_str = System.Text.Encoding.Default.GetString(code);
                byte[] size = new byte[32];
                bytesRead = clientStream.Read(size, 0, 32);
                string size_str = System.Text.Encoding.Default.GetString(size);
                byte[] res = new byte[Convert.ToInt32(size_str, 2) * 8];
                bytesRead = clientStream.Read(res, 0, Convert.ToInt32(size_str, 2) * 8);
                string rooms_str = System.Text.Encoding.Default.GetString(res);
                if (Convert.ToInt32(code_str, 2) == 1)
                {
                    Response response = JsonConvert.DeserializeObject<Response>(Translations.binaryToString(rooms_str));
                    if(response.status == 1)
                    {
                        AdminRoom r = new AdminRoom(_quiet, false);
                        this.Close();
                        r.ShowDialog();
                    }
                    else
                    {
                        notify.Text = "Room is either full or game has started";
                    }
                    
                }
                else
                {
                    ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(Translations.binaryToString(rooms_str));
                    notify.Text = response.message;
                }
            }
        }

        private void sign_out_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void shop_Click(object sender, RoutedEventArgs e)
        {

        }

        private void create_Click(object sender, RoutedEventArgs e)
        {
            stopFlag = true;
            while(stopFlag)
            {}
            bgWorker.CancelAsync();
            Audio.mediaPlayer.Close();
            Create build = new Create(_quiet);
            this.Close();
            build.ShowDialog();
        }

        private void lead_Click(object sender, RoutedEventArgs e)
        {

        }

        private void profile_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
