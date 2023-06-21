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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;
using System.Windows.Media;
using System.IO;
using Newtonsoft.Json;
using System.Net.Sockets;
using System.Drawing;

namespace Client
{
    /// <summary>
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {

        public Menu()
        {
            InitializeComponent();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
            openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\theme.mp3";
            Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
            Audio.mediaPlayer.Play();

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
            RoomData[] roomdatas = new RoomData[response.rooms.Length / 6];
            for (int i = 0; i < response.rooms.Length / 6; i++)
            {
                roomdatas[i] = new RoomData(int.Parse(response.rooms[i * 6]), response.rooms[i * 6 + 1], int.Parse(response.rooms[i * 6 + 2]), int.Parse(response.rooms[i * 6 + 3]), int.Parse(response.rooms[i * 6 + 4]), int.Parse(response.rooms[i * 6 + 5]));
            }
            for (int i = 0; i < roomdatas.Length; i++)
            {
                if (roomdatas[i].isActive == 0)
                {
                    listBox.Items.Add(roomdatas[i].id + " " + roomdatas[i].name);
                }
                
            }
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
        public void rest()
        {
            while (listBox.Items.Count > 0)
            {
                listBox.Items.RemoveAt(listBox.Items.Count - 1);
            }
        }

        private void ready_Click(object sender, RoutedEventArgs e)
        {

        }

        private void sign_out_Click(object sender, RoutedEventArgs e)
        {

        }

        private void shop_Click(object sender, RoutedEventArgs e)
        {

        }

        private void create_Click(object sender, RoutedEventArgs e)
        {
            
            Audio.mediaPlayer.Close();
            Create build = new Create();
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
