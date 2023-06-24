using Microsoft.Win32;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
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
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for Create.xaml
    /// </summary>
    public partial class Create : Window
    {
        bool _quiet = false;
        public Create(bool quiet)
        {
            _quiet = quiet;
            InitializeComponent();
            for (int i = 1; i <= 10; i++)
            {
                numOfQ.Items.Add(i);
                time.Items.Add(i * 5);
            }
            if (!quiet)
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "MP3 files (*.mp3)|*.mp3|All files (*.*)|*.*";
                openFileDialog.FileName = Directory.GetCurrentDirectory() + "\\freddys.mp3";
                Audio.mediaPlayer.Open(new Uri(openFileDialog.FileName));
                Audio.mediaPlayer.Play();
            }

        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void create_Click(object sender, RoutedEventArgs e)
        {
            
            if(name.Text != "")
            {
                string players = numOfPlayers.Text;
                if (players.All(char.IsNumber))
                {
                    CreateRoomRequest req = new CreateRoomRequest(name.Text, int.Parse(players), int.Parse(numOfQ.Text), int.Parse(time.Text));
                    string msg = Convert.ToString(8, 2);
                    msg = Translations.padLeft(msg, 8);
                    string json = JsonConvert.SerializeObject(req);
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
                    clientStream.Flush();
                    AdminRoom r = new AdminRoom(_quiet, true);
                    this.Close();
                    r.ShowDialog();

                }
            }
        }

        private void _return_Click(object sender, RoutedEventArgs e)
        {
            Menu r = new Menu(_quiet);
            this.Close();
            r.ShowDialog();
        }
    }
}
